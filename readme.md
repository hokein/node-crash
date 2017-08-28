
## Reproduce steps

```
$ cd <path-to-repo>/third_party/node
$ ./configure --shared --without-inspector --without-snapshot --without-intl
$ cd ../../
$ gyp --depth .  -f ninja main.gyp -Icommon.gypi -Ithird_party/node/common.gypi
$ ninja -C out/Debug main
$ ./out/Debug/main // bomb: crash!
```
