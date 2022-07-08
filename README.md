# IniLib
This is a personal project - a simple parser &amp; writer for the .ini format, written in c++.
Currently in its most basic and core form it is able to parse basic .ini syntax into a simple object.
It is to be changed and expanded upon in the near-ish future.

When completed it will contain such features as: <ul>
  <li> Extensive sub-secttion trees parsing </li>
  <li> Default-type deduced fields, able to parse ints, doubles, booleans and chars and freely convert between them </li>
  <li> Parser config to determine the default behavior of the parser, also recognizable from within the parsed file </li>
  <li> An object factory to create and write data into an .ini file. </li>
  <li> TOML-like array keys </li>
</ul>

Currently all documentation is contained within the header files.
