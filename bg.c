/* displays an image or sets root background
 * PUBLIC DOMAIN - CC0 http://creativecommons.org/publicdomain/zero/1.0/
 * J.Mayo 2013
 *
 * gcc -Wall -W -g3 -o background background.c -lX11 -lImlib2
 *
 */
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xcomposite.h>
#include <Imlib2.h>


struct screenAttributes {
    int height;
    int width;
};
struct screenAttributes screenAttr;
void initializeScreenAttributes(Screen *screen) {
    screenAttr.height=screen->height;
    screenAttr.width=screen->width;
}



int main(int argc, char **argv)
{
    Imlib_Image img;
    Display *dpy;
    Pixmap pix;
    Window root;
    Screen *scn;

   // Window topPanel;

    int width, height;
    const char *filename = "/sampleImage.png";


    img = imlib_load_image(filename);
    if (!img) {
        fprintf(stderr, "%s:Unable to load image\n", filename);
        goto usage;
    }
    imlib_context_set_image(img);
    width = imlib_image_get_width();
    height = imlib_image_get_height();

    dpy = XOpenDisplay(NULL);
    if (!dpy) return 0;

    scn = DefaultScreenOfDisplay(dpy);
    root = DefaultRootWindow(dpy);

    pix = XCreatePixmap(dpy, root, width, height,32); //when depth is set to 24 it just works, but when it is set to 32 it fails.



    //scale the image
    initializeScreenAttributes(scn);
    imlib_blend_image_onto_image(img,0,0,0,width,height,0,0,
                                screenAttr.width, screenAttr.height);



    imlib_context_set_display(dpy);
    imlib_context_set_visual(DefaultVisualOfScreen(scn));
    imlib_context_set_colormap(DefaultColormapOfScreen(scn));
    imlib_context_set_drawable(pix);

    imlib_render_image_on_drawable(0, 0);
    XSetWindowBackgroundPixmap(dpy, root, pix);
    XClearWindow(dpy, root);



    while (XPending(dpy)) {
        XEvent ev;
        XNextEvent(dpy, &ev);
    }
    XFreePixmap(dpy, pix);
    imlib_free_image();
    sleep(10);
    //XFreePixmap(dpy, pix);
    //imlib_free_image();
    XCloseDisplay(dpy);
    return 0;
usage:
    fprintf(stderr, "usage: %s <image_file>\n", argv[0]);
    return 1;
}