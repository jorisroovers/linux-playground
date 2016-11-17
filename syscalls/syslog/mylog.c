// http://man7.org/linux/man-pages/man3/syslog.3.html

#include <syslog.h>

int main(int argc, char **argv) {

    //---------- OPEN LOG -----------------
    // What to prepend to every log. If NULL then the program name is prepended
    const char *ident = "MYLOG";

    // How to open the log: LOG_ODELAY -> only open on writing first message
    int option = LOG_ODELAY;

    // facility = who's logging, alternatives: LOG_KERN (kernel logs), LOG_CRON (cron job logs),
    // LOG_AUTH (security logs), etc
    int facility = LOG_USER;

    // actually open the log
    openlog(ident, option, facility);

    // ----------- SYSLOG -------------------
    const char *message = "This is a test message";
    syslog(LOG_INFO, "%s", message); // on ubuntu: logged to /var/log/syslog


    // ---------- CLOSE LOG -----------------
    closelog(); // call is optional and has no arguments


    return 0;
}