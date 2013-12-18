--- plugins/bladesio1/gui.c.orig	2013-09-10 15:56:22.000000000 +0200
+++ plugins/bladesio1/gui.c	2013-09-10 15:59:32.000000000 +0200
@@ -26,8 +26,6 @@
 #include <gtk/gtk.h>
 
 #include <sys/socket.h>
-#include <sys/ioctl.h>
-#include <linux/if.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <netdb.h>
@@ -40,6 +38,11 @@
 
 /***************************************************************************/
 
+#ifdef __linux__
+
+#include <sys/ioctl.h>
+#include <linux/if.h>
+
 #define MAXINTERFACES 16
 
 void sockGetIP(char *IPAddress) {
@@ -67,6 +70,22 @@
 	}
 }
 
+#else
+
+void sockGetIP(char *IPAddress) {
+    struct hostent *host;
+    char str[256];
+
+    gethostname(str, 256);
+    host = gethostbyname(str);
+
+    if (host != NULL)
+        strcpy(IPAddress, inet_ntoa(*((struct in_addr *)host->h_addr_list[0])));
+    else strcpy(IPAddress, "127.0.0.1");
+}
+
+#endif
+
 void cfgSysMessage(const char *fmt, ...) {
 	GtkWidget *MsgDlg;
 	va_list list;
