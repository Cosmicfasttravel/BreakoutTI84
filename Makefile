# ----------------------------
# Program Options
# ----------------------------

NAME = Asteriod
ICON = obj/icon.png
DESCRIPTION  = "a very fun game"
COMPRESSED = NO
HAS_PRINTF = NO
CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
