# FindStr<br>
## Finds a matching string in files<br><br>

## Usage: findstr [OPTIONS] string<br>
### Options:<br>
### -h,--help                   Print this help message and exit<br><br>

###  -p,--path TEXT:DIR [../]   Path to search<br>
###                             Defaults to current directory<br><br>

###  -z,--size UINT:SIZE [b,    kb(=1000b), kib(=1024b), ...] [0]<br>
###                             Ignore files over size (bytes)<br>
###                             Defaults to 0 (disabled)<br><br><br>


### Example: findstr --path "../amongus" --size 10kb "sus"