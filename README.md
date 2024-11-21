<div align="center">

# `Citch`

<h3>
  Fast system fetch written in <code>👑 C++ 👑</code>
</h3>
<br>

![License](https://img.shields.io/github/license/xeyossr/citch?style=for-the-badge)
![Commits](https://img.shields.io/github/commit-activity/m/xeyossr/citch?style=for-the-badge)
![AUR](https://img.shields.io/aur/version/citch?style=for-the-bade)
![GitHub Repo stars](https://img.shields.io/github/stars/xeyossr/citch?style=for-the-badge)
![GitHub issues](https://img.shields.io/github/issues/xeyossr/citch?style=for-the-badge)
![GitHub pull requests](https://img.shields.io/github/issues-pr/xeyossr/citch?style=for-the-badge)

![GitHub release (latest by date)](https://img.shields.io/github/v/release/xeyossr/citch?style=for-the-badge)

</div>

**Citch** is a small and fastsystem fetch tool written fully in `C++`. If you're familiar with nitch (btw written in `Nim`), Citch is essentially its C++ version.

Why C++? Well, because I started learning C++ and couldn’t think of anything else, lmao

<br>

# Installation

If you are using Arch Linux or an Arch-based distribution, you can download `citch` from AUR:
```bash
yay -S citch
```

If you are not using an Arch-based distribution:
```bash
wget https://raw.githubusercontent.com/xeyossr/citch/main/install.sh && sh install.sh
```

# Usage

```
citch
```

flags:

```
 -gc --gen-config   | generate config file
```

<br>

# Configuration

> Before doing these, you need to create a configuration file with the `--gen-config` flag.

### `~/.config/citch/config.json` - config file

```json
{
  "modules": {
    "banner": true,
    "colors": true,
    "distro": true,
    "hostname": true,
    "kernel": true,
    "memory": true,
    "packages": true,
    "shell": true,
    "uptime": true,
    "username": true
  }
}
```

# Building 📦

### 1) clone repo

```fish
git clone https://github.com/xeyossr/citch
```

### 2) change dir (cd) to `citch`

```fish
cd citch
```

### 3) build program with `g++`

```fish
g++ citch.cpp -o citch
```

<br>

# File architecture 📁

```fish
citch
├── citch.cpp
├── dist
│   └── citch
├── install.sh
├── LICENSE
├── modules
│   ├── banners.cpp
│   ├── fetch.h
│   └── json.hpp
└── README.md

3 directories, 8 files
```

# Thanks for ideas & examples 💬

- [nitch](https://github.com/ssleert/nitch)
- [pfetch](https://github.com/dylanaraps/pfetch/)
- [neofetch](https://github.com/dylanaraps/neofetch)
