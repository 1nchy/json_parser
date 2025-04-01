#ifndef _ICY_JSON_PARSER_HPP_
#define _ICY_JSON_PARSER_HPP_

#include <string>
// #include <unordered_map>
#include <map>
#include <variant>
#include <vector>

#include <fstream>

#include <stdexcept>

namespace icy {

struct json;

struct json {
public:
    using monostate = std::monostate;
    using boolean = bool;
    using integer = long;
    using floating_point = double;
    using string = std::string;
    using array = std::vector<json>;
    // using object = std::unordered_map<string, json>;
    using object = std::map<string, json>;
    using value_type = std::variant<monostate, boolean, integer, floating_point, string, array, object>;
    struct exception;
    struct bad_content;
    struct bad_cast;
    struct bad_json;
public:
    json();
    json(const json&) = default;
    json(json&&) = default;
    json(const value_type& _value);
    json(value_type&& _value);
    ~json() = default;
public:
    /**
     * @note copy value for hierarchical assignment
     */
    auto operator=(const json&) -> json&;
    auto operator=(json&&) -> json&;
    auto operator=(const value_type&) -> json&;
    auto operator=(value_type&&) -> json&;
    auto operator==(const json&) const -> bool;
    auto operator==(const value_type&) const -> bool;
    auto operator!=(const json&) const -> bool;
    auto operator!=(const value_type&) const -> bool;
    /**
     * @brief access value (create value if the key does not exist)
     * @throw `bad_cast` if not an object
     * @note monostate -> object
     */
    auto operator[](const string&) -> json&;
    /**
     * @brief access value
     * @throw `bad_cast` if not an object
     */
    auto operator[](const string&) const -> const json&;
    /**
     * @brief access element
     * @throw `bad_cast` if not an array
     */
    auto operator[](size_t) -> json&;
    /**
     * @brief access element
     * @throw `bad_cast` if not an array
     */
    auto operator[](size_t) const -> const json&;
public:
    /**
     * @brief push element
     * @throw `bad_cast` if not an array
     * @note monostate -> array
     */
    void push(const json&);
    /**
     * @brief push element
     * @throw `bad_cast` if not an array
     * @note monostate -> array
     */
    void push(json&&);
    /**
     * @brief push element
     * @throw `bad_cast` if not an array
     * @note monostate -> array
     */
    void push(const value_type&);
    /**
     * @brief push element
     * @throw `bad_cast` if not an array
     * @note monostate -> array
     */
    void push(value_type&&);
    /**
     * @brief push element
     * @throw `bad_cast` if not an array
     * @note monostate -> monostate
     */
    void pop();
    /**
     * @brief insert key and value
     * @throw `bad_cast` if not an object
     * @note monostate -> object
     */
    void insert(const string&, const json&);
    /**
     * @brief insert key and value
     * @throw `bad_cast` if not an object
     * @note monostate -> object
     */
    void insert(const string&, json&&);
    /**
     * @brief insert key and value
     * @throw `bad_cast` if not an object
     * @note monostate -> object
     */
    void insert(const string&, const value_type&);
    /**
     * @brief insert key and value
     * @throw `bad_cast` if not an object
     * @note monostate -> object
     */
    void insert(const string&, value_type&&);
    /**
     * @brief insert key and value
     * @throw `bad_cast` if not an object
     * @note monostate -> monostate
     */
    void erase(const string&);
    /**
     * @brief clear
     * @throw `bad_cast` if not an array or object
     * @note monostate -> monostate
     */
    void clear();
    /**
     * @brief empty
     * @return whether empty or monostate
     * @throw `bad_cast` if not an array or object
     * @note monostate -> monostate
     */
    auto empty() const -> bool;
    /**
     * @brief size
     * @return container size or 0 if monostate
     * @throw `bad_cast` if not an array or object
     * @note monostate -> monostate
     */
    auto size() const -> size_t;
    /**
     * @brief access value
     * @throw `bad_cast` if not an object
     */
    auto at(const string&) -> json&;
    /**
     * @brief access value
     * @throw `bad_cast` if not an object
     */
    auto at(const string&) const -> const json&;
    /**
     * @brief access element
     * @throw `bad_cast` if not an array
     */
    auto at(size_t) -> json&;
    /**
     * @brief access element
     * @throw `bad_cast` if not an array
     */
    auto at(size_t) const -> const json&;
    /**
     * @brief whether the key exists
     * @throw `bad_cast` if not an object
     */
    auto contains(const string&) const -> bool;
    /**
     * @brief return variant
     */
    auto value() -> value_type&;
    /**
     * @brief return variant
     */
    auto value() const -> const value_type&;
    /**
     * @brief return data
     * @tparam _Tp data type
     * @throw `bad_cast` if a wrong type is given
     */
    template<typename _Tp> auto value() -> _Tp&;
    /**
     * @brief return data
     * @tparam _Tp data type
     * @throw `bad_cast` if a wrong type is given
     */
    template<typename _Tp> auto value() const -> const _Tp&;
public:
    /**
     * @brief load string to json
     * @param _s ascii string
     * @return json
     * @throw `bad_content`
     */
    static auto load(const std::string& _s) -> json;
    /**
     * @brief load file stream to json
     * @param _ifs json file input stream
     * @return json
     * @throw `bad_content`
     */
    static auto load(std::ifstream& _ifs) -> json;
    /**
     * @brief dump json to string
     * @param _n json
     * @return ascii string
     * @throw `bad_json`
     */
    static auto dump(const json& _n) -> std::string;
    /**
     * @brief dump json to file stream
     * @param _n json
     * @param _ofs json file output stream
     * @param _indent indent for json file (0 by default)
     * @note no formatting when `_indent == 0`
     * @throw `bad_json`
     */
    static auto dump(const json&, std::ofstream& _ofs, size_t _indent = 0) -> void;
    /**
     * @brief dump json to string
     * @return ascii string
     * @throw `bad_json`
     */
    auto dump() const -> std::string;
    /**
     * @brief dump json to file stream
     * @param _ofs json file output stream
     * @param _indent indent for json file (0 by default)
     * @note no formatting when `_indent == 0`
     * @throw `bad_json`
     */
    auto dump(std::ofstream& _ofs, size_t _indent = 0) const -> void;
private:
    value_type _value;
};


struct json::exception : public std::exception {
public:
    explicit exception(const std::string&);
    explicit exception(const char*);
    exception(const exception&) noexcept = default;
    exception(exception&&) noexcept = default;
    exception& operator=(const exception&) noexcept = default;
    exception& operator=(exception&&) noexcept = default;
    virtual ~exception() noexcept = default;
    virtual const char* what() const noexcept;
public:
    static constexpr inline const char* RIGHT_CURLY_EXPECTED = "right curly expected";
    static constexpr inline const char* RIGHT_SQUARE_EXPECTED = "right square expected";
    static constexpr inline const char* TRAILING_COMMA = "trailing comma";
    static constexpr inline const char* COLON_EXPECTED = "colon expected";
    static constexpr inline const char* VALUE_EXPECTED = "value expected";
    static constexpr inline const char* STRING_KEY_EXPECTED = "string key expected";
    static constexpr inline const char* END_OF_NUMBER_EXPECTED = "end of number expected";
    static constexpr inline const char* END_OF_STRING_EXPECTED = "end of string expected";
    static constexpr inline const char* END_OF_FILE_EXPECTED = "end of file expected";
    static constexpr inline const char* NOT_THE_TYPE = "not the type";
    static constexpr inline const char* NOT_AN_OBJECT = "not an object";
    static constexpr inline const char* NOT_AN_ARRAY = "not an array";
    static constexpr inline const char* NOT_AN_ARRAY_OR_OBJECT = "not an array or object";
private:
    std::string _msg;
};

/**
 * @brief exception in loading json string
 */
struct json::bad_content : public json::exception {
public:
    explicit bad_content(const std::string&);
    explicit bad_content(const char*);
    bad_content(const bad_content&) noexcept = default;
    bad_content(bad_content&&) noexcept = default;
    bad_content& operator=(const bad_content&) noexcept = default;
    bad_content& operator=(bad_content&&) noexcept = default;
    virtual ~bad_content() noexcept = default;
};
/**
 * @brief exception in type casting
 */
struct json::bad_cast : public json::exception {
public:
    explicit bad_cast(const std::string&);
    explicit bad_cast(const char*);
    bad_cast(const bad_cast&) noexcept = default;
    bad_cast(bad_cast&&) noexcept = default;
    bad_cast& operator=(const bad_cast&) noexcept = default;
    bad_cast& operator=(bad_cast&&) noexcept = default;
    virtual ~bad_cast() noexcept = default;
};
/**
 * @brief exception in dumping json
 */
struct json::bad_json : public json::exception {
public:
    explicit bad_json(const std::string&);
    explicit bad_json(const char*);
    bad_json(const bad_json&) noexcept = default;
    bad_json(bad_json&&) noexcept = default;
    bad_json& operator=(const bad_json&) noexcept = default;
    bad_json& operator=(bad_json&&) noexcept = default;
    virtual ~bad_json() noexcept = default;
};



template <typename _Tp> auto json::value() -> _Tp& {
    if (std::holds_alternative<_Tp>(_value)) {
        return std::get<_Tp>(_value);
    }
    throw bad_cast(exception::NOT_THE_TYPE);
}
template <typename _Tp> auto json::value() const -> const _Tp& {
    if (std::holds_alternative<_Tp>(_value)) {
        return std::get<_Tp>(_value);
    }
    throw bad_cast(exception::NOT_THE_TYPE);
}

}

#endif // _ICY_JSON_PARSER_HPP_