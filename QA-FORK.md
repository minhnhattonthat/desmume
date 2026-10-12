# DeSmuME QA fork

Small changes on top of upstream DeSmuME for scripted, headless test runs (driven by a harness such as the
translate-retro-game skill's `emu.py`). Upstream behaviour is unchanged unless a new flag or Lua call is used.

## Command line (Windows frontend)

| Flag | Effect |
|---|---|
| `--ini FILE` | Use FILE instead of `desmume.ini` beside the exe. One ini per run: nothing shared, runs can go in parallel. |
| `--lua FILE` | Run a Lua script once the ROM loads (no "auto-load Lua" ini setting needed). |
| `--headless` | Hide the main and Lua windows, and keep emulating while unfocused. |

Existing flags that scripted runs want: `--disable-limiter`, `--jit-enable`, `--disable-sound`.

## Lua

- `memory.registerexec` hooks fire under the JIT too (previously interpreter only). Compiled blocks pick up hook
  changes at the next frame.
- `savestate.save(path)` / `savestate.load(path)` accept a file path as well as a slot number.
- `gui.savepng(path[, "top"|"bottom"])` writes the screen straight to PNG.

## Build (Windows, Visual Studio 2022 or later)

```
msbuild desmume/src/frontend/windows/DeSmuME.sln /p:Configuration="Release Fastbuild" /p:Platform=x64
```

- If the build fails with `'un7z_and_touch.bat' is not recognized`, unset `NoDefaultCurrentDirectoryInExePath` in
  that shell first.
- Ship the exe with `desmume/src/frontend/windows/.libs/x64/lua51.dll` and `lua5.1.dll` beside it (unpacked by the
  build); no separate Lua download needed.
- Don't run it from the system temp directory: DeSmuME switches to a per-user settings path there and crashes at start.

## Known

- With the JIT, a few games show a grey screen after loading a state until the next input or redraw; the
  interpreter (no `--jit-enable`) renders at once. Same as upstream.

License: GPL-2.0-or-later, as upstream.
