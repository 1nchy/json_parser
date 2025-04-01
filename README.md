# JSON PARSER

A naive json parser, just for practise.

### ENVIRONMENT

C++20 standard is required.

Header files `filesystem`, `variant`, `concept`, `source_location` are all required.

Here are third libraries: 
[1nchy/finite_state_machine](https://github.com/1nchy/finite_state_machine), 
[tl/expected](https://github.com/TartanLlama/expected)

### USAGE

This is a library including header files and source files.

For more details about the structure, view [1nchy/third_lib_template]
(https://github.com/1nchy/third_lib_template).

### EXAMPLE

##### Read JSON from a string or file

The `json` class provides APIs `json::load` to create a `json` value.

~~~c++
using namespace icy;
// ...
json j1 = json::load("[1, 2]");
std::ifstream file("configuration.json");
json j2 = json::load(file);
~~~

If an invalid json string is provided,
exception `json::bad_content` would be thrown.
Additionally, the exception would take an error message.

~~~c++
using namespace icy;
// ...
try { json j = json::load("[,]"); }
catch (const json::bad_content& e) {} // e.what() == "value expected"
~~~

##### Dump JSON to a string or file

The `json` class provides APIs `json::dump` to dump `json` value.

~~~c++
using namespace icy;
// ...
json j = json::load("{\"truth\": [], \"pi\": 3.14}");
std::string s = j.dump(); // {"truth":[],"pi":3.14}
std::ofstream file("configuration.json");
j.dump(file, 4); // json::dump(j, file, 4);
// {
//     "truth": [],
//     "pi": 3.14
// }
~~~

`json` class provides member methods and static methods for dumping.
The `json` value would be the first argument in static methods.

Methods for dumping to file provide an additional arugment `indent`,
which is used to format the dump.

When `indent` argument is not provided or equal to 0,
The dump would not be formatted, and there is no spaces in the dump.

##### STL-like access

Create an array using STL-like method.

~~~c++
json j;
j.push(0); j.push(1); // [0, 1], j is an array
j.pop(); // [0]
j.size(); // 1
j.empty(); // false
j.clear(); // nothing in array
~~~

Create an object using STL-like method.

~~~c++
json j;
j["one"] = 1; // {"one":1}, j is an object
j.contains("one"); // true
j.insert("two", 2); // {"one":1,"two":2}
j.erase("one"); // {"two":2}
j.size(); // 1
j.empty(); // false
j.clear(); // nothing in object
~~~

Some methods are only availiable for certain types.
If an appropriate method is called,
exception `json::bad_cast` will be thrown.
Additionally, the exception would take an error message.

~~~c++
json j = json::load("[\"zero\"]"); // j is an array
try { j.contains("zero"); }
catch (const json::bad_cast& e) {} // e.what() == "not an object"
~~~

Another example:

~~~c++
json j = json::load("{}"); // j is an object
try { j.push("zero"); }
catch (const json::bad_cast& e) {} // e.what() == "not an array"
~~~

Specially, monostate json can call most of methods without exception.
It would transit to a type,
if the method is only available for the certain type.

~~~c++
json j; // j is monostate
j.push(0); // j is an array now
~~~

##### Access value

Template `json::value` provide the ability of accessing value.

In comparison or assignment, we overwrote relative operator,
and there's no need to access value directly.

~~~c++
json j = json::load("[3]");
j[0].value<json::integer>(); // 3
j[0] == 3; // true
j[0] = j; // [[3]]
~~~

If a wrong type argument is given in template `json::value`,
exception `json::bad_cast` would be thrown.

~~~c++
json j = json::load("3");
try { j.value<json::boolean>(); }
catch (const json::bad_cast& e) {} // e.what() == "not the type"
~~~
