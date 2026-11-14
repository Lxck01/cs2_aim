Create a file named `aim.cfg` in the same directory as the application and paste the configuration below.

You can edit the settings to your preference. Changes will take effect after restarting the application.

```ini
# Keybinds:
# MOUSE4, MOUSE5, LEFT, RIGHT, MIDDLE
# SHIFT, CTRL, ALT, SPACE
# INSERT, DELETE, HOME, END, PGUP, PGDN
# F1-F12, A-Z, 0-9
# Raw virtual-key codes are also supported (e.g. 0x06).

aim_key      = MOUSE5
exit_key     = END

fov          = 6.0
smooth       = 4.0
max_deg_tick = 2.0
head_bone    = 6
tick_ms      = 4

# Team filtering
team_check   = true

# Visibility filtering
# Requires off::m_bSpotted in offsets.h to be verified
# for your current game build.
# Incorrect offsets may cause visibility checks to behave unexpectedly.
vis_check    = false
```
