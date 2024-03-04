
template<typename T>
class UniquePtr {
    private:
    T* object_ptr;

    public:
    UniquePtr(const T& object): object_ptr(new T(object)) {
        
    }

    UniquePtr(T&& object) {

    }

    operator bool() { return object_ptr != nullptr; }
};

int main() {
    return 0;
}
