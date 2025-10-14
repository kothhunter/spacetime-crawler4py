#
# $Id: dot.login,v 1.6 2002/09/11 23:04:54 fiorello Exp $
# $Source: /usr/src/opt/local/etc/skel/RCS/dot.login,v $
#
#emulate 'stty dec'
stty kill ^u werase ^w rprnt ^r flush ^o lnext ^v intr ^c quit ^\\ erase ^\?
set ignoreeof

if ( -e .login.new) then
    set newfile = .login.new
    set newprog = /bin/mv
else
    set newfile = /opt/local/etc/skel/acct/.login.new
    set newprog = /bin/cp
endif

(/opt/X11R6.3/bin/xterm -e /usr/bin/yppasswd) >& /dev/null

if ($status == 0 ) then
    $newprog $newfile .login
    source .login
else

    echo ""
    echo "         **************************************************"
    echo ""
    echo "                  WELCOME TO " `hostname`
    echo ""
    echo "         **************************************************"
    echo ""
    echo ""
    echo "You must now change your password."
    echo "Guidelines for passwords:"
    echo "  Choose a password that contains at least 6 characters."
    echo "  Choose a password that is not a word in the dictionary."
    echo "  Use numbers, spaces, or punctuation marks in your password."
    echo "  Do not choose your name, or the name of a friend."
    echo "  Do not choose your address, drivers license number, or"
    echo "    any other password that can be easily guessed."
    echo ""
    echo "If you have any questions, please come to the Consultants in CS 346."
    echo ""
    yppasswd $USER

    if ($status == 0 ) then
        $newprog $newfile .login
        source .login
    endif

endif
