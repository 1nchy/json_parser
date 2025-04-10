# JSON PARSER

A naive json parser, just for practise.

## ENVIRONMENT

C++20 standard is required.

Header files `filesystem`, `variant`, `concept`, `source_location` are all required.

Here are third libraries: 
[1nchy/finite_state_machine](https://github.com/1nchy/finite_state_machine), 
[tl/expected](https://github.com/TartanLlama/expected)

## USAGE

This is a library including header files and source files.

For more details about the structure, view 
[1nchy/third_lib_template](https://github.com/1nchy/third_lib_template).

## EXAMPLE

#### Read JSON from a string or file

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

#### Dump JSON to a string or file

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

Methods for dumping to file provide an additional argument `indent`,
which is used to format the dump.

When `indent` argument is not provided or equal to 0,
The dump would not be formatted, and there is no spaces in the dump.

#### JSON construction / assignment in code

Excluding the normal constructor,
`initializer_list` provides a more convenient way to construct array.

~~~c++
json j1 {1, 2, 3}; // [1, 2, 3]
json j2 {{"one", 1}, {"two", 2}}; // {"one": 1, "two": 2}
json j3 {{"one", 1}, {"two", 2}, {true, 3}}; // [["one", 1], ["two", 2], [true, 3]]
~~~

For some ambiguous circumstance,
`json::make_array` and `json::make_object` will treat `initializer_list`
as array and key-value pair respectively.

Specifically, an `initializer_list` will be treated as key-value pair,
only if **all of elements contains 2 elements and the type of the first one is string**.

~~~c++
json j1 = json::make_array({1, 2, 3}); // [1, 2, 3]
json j2 = json::make_array({{"one", 1}, {"two", 2}}); // [["one", 1], ["two", 2]]
json j3 = json::make_object({{"one", 1}, {"two", 2}}); // {"one": 1, "two": 2}
~~~

`operator=` has been overridden in `json` class,
so the value can be assigned directly.

~~~c++
json j = json::make_array(); // array
j = 1; // integer now
j = true; // boolean now
j = json::make_object(); // object
~~~

#### STL-like access

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
If an inappropriate method is called,
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
if the method is only available for the certain type,

~~~c++
json j; // j is monostate
j.push(0); // j is an array now
~~~

But if the method has not changed itself,
such as `pop`, `erase`, and member methods with `const` modifier,
the json type will not transit.

~~~c++
json j; // j is monostate
j.pop(); // j is still monostate
j.erase("zero"); // j is still monostate
j.clear(); // j is still monostate
j.empty(); // j is still monostate
j.size(); // j is still monostate
~~~

#### Access value

Template `json::as` provides the ability of accessing value.

In comparison or assignment, we overwrote relative operator,
and there's no need to access value directly.

~~~c++
json j = json::load("[3]");
j[0].as<json::integer>(); // 3
j[0] == 3; // true
j[0] = j; // [[3]]
~~~

If a wrong type argument is given in template `json::as`,
exception `json::bad_cast` would be thrown.

~~~c++
json j = json::load("3");
try { j.as<json::boolean>(); }
catch (const json::bad_cast& e) {} // e.what() == "not the type"
~~~

Overloaded template `json::as` also provides a way to access value with no exception.
It returns the default value, when a wrong type argument is given.

~~~c++
json j = json::load("[3]");
const auto i = j.as<json::integer>(1); // i = 1
~~~
