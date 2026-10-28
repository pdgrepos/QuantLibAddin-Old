#ifndef LocalEnumRegistry_hpp
#define LocalEnumRegistry_hpp

#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <memory>
#include <algorithm>

template <typename T>
class LocalEnumRegistry {
public:
    static LocalEnumRegistry& instance() {
        static LocalEnumRegistry inst;
        return inst;
    }

    // 1. Overload per Oggetti/Istanze passati per Valore o Riferimento Const
    void registerType(const std::string& key, const T& value) {
        map_[normalize(key)] = [value]() -> T { return value; };
    }

    // 2. Overload per Puntatori grezzi (es. new QuantLib::Australia())
    // Prende possesso del puntatore in modo sicuro e pulito
    template <typename Derived>
    void registerType(const std::string& key, Derived* ptr) {
        // Incapsula in uno shared_ptr locale per evitare Memory Leak
        std::shared_ptr<Derived> smartPtr(ptr);
        map_[normalize(key)] = [smartPtr]() -> T { return *smartPtr; };
    }

    // 3. Overload per costruttori/Factory tramite Lambda (opzionale, ma comodissimo)
    void registerType(const std::string& key, std::function<T()> factory) {
        map_[normalize(key)] = factory;
    }

    // Recupero del valore / istanza
    T parse(const std::string& key) const {
        auto it = map_.find(normalize(key));
        if (it != map_.end()) {
            return it->second(); // Esegue la factory e restituisce T (es. QuantLib::Calendar)
        }
        throw std::runtime_error("Key not found in LocalEnumRegistry: " + key);
    }

    // Operatore () per mantenere la sintassi identica ad ObjectHandler: Create<T>()("Key")
    T operator()(const std::string& key) const {
        return parse(key);
    }

    //! Convert a list of strings into the associated enumerations.
    template <class T>
    std::vector<T> vectorStringToEnum(
        const std::vector<std::string> ids,
        const std::string &paramName) {

        try {
            std::vector<T> returnValue;
            for (std::vector<std::string>::const_iterator i = ids.begin(); i != ids.end(); ++i)
                returnValue.push_back(parse(*i));
            return returnValue;
        }
        catch (const std::exception &e) {
            OH_FAIL("vectorStringToEnum: error converting parameter '" << paramName
                << "' to type '" << typeid(T).name() << "' : " << e.what());
        }
    }

private:
    LocalEnumRegistry() = default;

    // Rende la ricerca case-insensitive (o toglie spazi) se desiderato
    static std::string normalize(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    std::unordered_map<std::string, std::function<T()>> map_;
};

#endif