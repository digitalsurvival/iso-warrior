#include <gtk/gtk.h>

extern GtkWidget* GBLmainWindow;

static const char* 
GBLprogramName = "ISO Master";

static const char* 
GBLauthors[2] = {
"Many thanks to all the following people:\n"
"\n"
"Andrew Smith\n"
"http://littlesvr.ca/misc/contactandrew.php\n"
"Summer 2005 - Fall 2006\n"
"- author and maintainer\n"
"\n"
"Barb Czegel\n"
"http://cs.senecac.on.ca/~barb.czegel/\n"
"Summer-fall 2005\n"
"- one of my teachers from Seneca College who has been kind enough to let me work on ISO Master as my systems project for two semesters\n"
"\n"
"The Samba Project\n"
"http://us2.samba.org/\n"
"December 2005\n"
"- most of the filename mangling code I copied from samba\n"
"\n"
"Tango Desktop Project\n"
"http://tango.freedesktop.org/Tango_Icon_Gallery\n"
"August 2006\n"
"- the 'drive-cdrom' icon used as the application icon\n"
"\n"
"Nicolas Devillard\n"
"http://ndevilla.free.fr/iniparser/\n"
"August 2006\n"
"- the excellent iniparser, for storing and reading config files\n"
"\n"
"",
NULL};

static const char* 
GBLcomments = "An application for editing ISO9660 images based on the "
              "bkisofs access library and the GTK2 GUI toolkit.";

static const char* 
GBLcopyright = "Copyright 2005-2006 Andrew Smith";

static const char* 
GBLwebsite = "http://littlesvr.ca/isomaster/";

static const char* 
GBLlicense = "GNU General Public Licence Version 2";

void showAboutWindowCbk(GtkMenuItem* menuItem, gpointer data)
{
    gtk_show_about_dialog(GTK_WINDOW(GBLmainWindow), 
                          "name", GBLprogramName,
                          "authors", GBLauthors,
                          "comments", GBLcomments,
                          "copyright", GBLcopyright,
                          "license", GBLlicense,
                          "website", GBLwebsite,
                          NULL);
    
    //~ GtkWidget* aboutDialog;
    
    //~ aboutDialog = gtk_about_dialog_new();
    
    //~ gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(aboutDialog), GBLprogramName);
    //~ gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(aboutDialog), GBLauthors);
    //~ gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutDialog), GBLcomments);
    //~ gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutDialog), GBLcopyright);
    //~ gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(aboutDialog), GBLlicense);
    //~ gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(aboutDialog), GBLwebsite);
    
    //~ gtk_widget_show(aboutDialog);
}