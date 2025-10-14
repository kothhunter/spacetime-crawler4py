# .profile
# This .profile file is for bourne type shells and is executed at login
# To use this file copy it to your home directory and name it .profile
# This and other "dot" files can be found at /opt/local/etc/skel

# NOTE - local variables, variables for this shell only, do not need to
# be exported.  Global variables, any variables you wish to pass on, must
# be exported with the 'export' command.  Normally it is done like this:
#
# 'VAR=value ; export VAR'
#

# Make sure files are NOT world readable
umask 077

# set up the PATH variable
PATH=/usr/bin:/bin:${PATH}


###############
# Set Prompts #
###############
# PS1 is your main prompt
PS1="${user}@`hostname` \$ "

# PS2 is the secondary prompt, if more input is needed
# The default for PS2 is > which may be mistaken for a re-direct
PS2="\\"

### check for HOSTNAME
HOSTNAME=$(hostname 2>/dev/null || hostname -f)

####################
# Export Variables #
####################
export PS1 PS2 PATH

###############
# Set Aliases #
###############

# Verify rm of files
alias rm="/bin/rm -i"

# Verify cp of files
alias cp="/bin/cp -i"

# Verify mv of files
alias mv="/bin/mv -i"

#######################
# Shell customization #
#######################
# if you're using bash, exec ~/.bashrc
if test -f ~/.bashrc ; then
	. ~/.bashrc 
fi
