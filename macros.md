Macros are as follows; They can be disabled by passing `-D__R49_NO_XXX`

```
__r49: If not specified, nothing I've done is used
__r49_modern_c: changes to make it compile on modern compilers (rename from __r49_required_changes)
	__r49_64bit: change a lot of places where `int` was used to `VALUE`, as they used to be the same size
__r49_critical_bugfix: without this, several critical bugs aren't handled
__r49_bufix: fixes a bunch of smaller bugs
__r49_recursion_limit: if set, specifies the stack size. if not set, then it segfaults when it gets too high
__r49_dev: debug stuff specifically for working on r49, not using it
```
__r49_ubfix: ???
__r49_use_includes: ???
