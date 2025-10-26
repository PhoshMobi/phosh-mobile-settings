# Configurable Tweaks support

## Introduction

This feature implements support for the YAML definition format implemented by
the now deprecated [postmarketOS Tweaks application][1].

Since the original documentation is incomplete, this serves as an up-to-date
reference that also includes notable changes from the original. While this
implementation largely strives to be compatible with the original, some features
are no longer as useful due to Linux phones gaining broader adoption and regular
settings applications implementing them. As such, they have not been implemented

If you see any justification for re-adding these features, patches are welcome!

 [1]: https://gitlab.postmarketos.org/postmarketOS/postmarketos-tweaks

## Backends

### gsettings

```yaml
backend: gsettings
gtype: boolean
key: org.postmarketos.Tweaks.coolsetting
```

Uses GSettings to read and write the settings. The key is the full path to the
setting. It's possible to set the key to a list of settings, in which case the
first one found will be used.

The gtype option is used to define which type the gsetting is in case it's
different than the type of the widget. This is mainly useful when things are
remapped.

### symlink

```yaml
backend: symlink
key: ~/.local/var/example.data
source_ext: false
```

This creates a symlink where the source is the input data from the user and
the target is the `key`.

If `source_ext` is true, the extension of the source file will be appended to
the key before using that as the target path for the symlink.

Setting the value to `None` will remove the symlink.

This backend is normally used with the file widget

### xresources

```yaml
backend: xresources
key: dwm.background
type: color
default: #BBBBBB
```

Reads and writes to ~/.Xresources. If a given key is available in that file, it
will be read on program startup, otherwise the default value from the setting
definition is used.
