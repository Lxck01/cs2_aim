## 🛠️ Build & Installation

1. 📂 Open the project in Visual Studio.
2. ⚙️ Set the build configuration to **Release** and the platform to **x64**.
3. 🔨 Press `Ctrl + Shift + B` to compile the project.
4. 📁 Navigate to the output directory:
   ```text
   source\repos\cs2_aim\x64\Release
   ```
5. 🚀 Run `cs2_aim.exe` as Administrator.

## ⚙️ Configuration

You can optionally create an `aim.cfg` file in the same directory as `cs2_aim.exe`.

📋 Paste the following configuration into the file:

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

### 📝 Configuration Notes

- 🎯 **aim_key:** Key used to activate aiming.
- 🚪 **exit_key:** Key used to exit the application.
- 🔭 **fov:** Field-of-view setting.
- 🎚️ **smooth:** Smoothing value.
- 📐 **max_deg_tick:** Maximum angular adjustment per tick.
- 🦴 **head_bone:** Target bone index.
- ⏱️ **tick_ms:** Update interval in milliseconds.
- 👥 **team_check:** Enables and disables aimbot on teammates.
- 👁️ **vis_check:** Stop/let the aimbot lock onto a hidden enemy.

💡 If `aim.cfg` is not present, the application will use its default configuration.
