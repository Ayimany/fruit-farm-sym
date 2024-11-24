#ifndef DYNAMIC_ARRAY_HH
#define DYNAMIC_ARRAY_HH

#include <functional>
#include <stdexcept>

namespace fmk { namespace util {
    // Use of vectors is forbidden. Custom dynamic array.
    // I assume smart pointers are also not allowed, so I will use raw pointers
    // This dynamic array is far from perfect, yet, it accomplishes the task
    // at hand.

    /**
     * Represents a dynamic array that can only allocate as many elements as it
     * contains.
     * @tparam obj_type_t The type of element to hold.
     */
    template <typename obj_type_t>
    class dynamic_array {
    public:
        using iterator   = obj_type_t *;
        using iterator_c = const obj_type_t *;

        explicit
        dynamic_array(size_t const prealloc)
            : _data(new obj_type_t[prealloc]())
            , _size(0)
            , _alloc(prealloc) {
        }

        explicit
        dynamic_array()
            : dynamic_array(10) {
        }

        ~dynamic_array() {
            this->cleanup();
        }

        [[nodiscard]] auto
        get(
            size_t index
        )
            -> obj_type_t & {
            if (index >= _size) {
                this->cleanup();

                throw std::runtime_error {
                    "Index " + std::to_string(index) +
                    " out of bounds for size " + std::to_string(_size)
                };
            }

            return _data[index];
        }

        auto
        insert(
            obj_type_t obj_type
        )
            -> void {
            if (_size == _alloc) {
                this->resize(_alloc + 1);
            }

            _data[_size++] = std::move(obj_type);
        }

        template <typename... arg_types_t>
        auto
        emplace(
            arg_types_t &&... args
        )
            -> void {
            static_assert(
                std::is_constructible<obj_type_t, arg_types_t...>::value,
                "Cannot construct the target object with the given arguments"
            );

            if (_size == _alloc) {
                this->resize(_alloc + 1);
            }

            _data[_size++] = obj_type_t { std::forward<arg_types_t>(args)... };
        }

        auto
        remove(
            const size_t index
        )
            -> void {
            if (index >= _size) {
                this->cleanup();

                throw std::runtime_error {
                    "Index " + std::to_string(index) +
                    " out of bounds for size " + std::to_string(_size)
                };
            }

            if (index != _size - 1) {
                for (size_t i = index; i < _size; ++i) {
                    _data[i - 1] = obj_type_t(std::move(_data[i]));
                }
            }

            _size--;
        }

        [[nodiscard]] auto
        size() const noexcept
            -> size_t {
            return _size;
        }

        iterator
        begin() {
            return _data;
        }

        iterator_c
        begin() const {
            return _data;
        }

        iterator
        end() {
            return _data + _size;
        }

        iterator_c
        end() const {
            return _data + _size;
        }

        [[nodiscard]] auto
        operator[](
            const size_t index
        )
            -> obj_type_t & {
            return this->get(index);
        }

    private:
        obj_type_t *_data;
        size_t      _size;
        size_t      _alloc;

        auto
        resize(
            const size_t alloc_count
        )
            -> void {
            auto *new_data = new obj_type_t[alloc_count];

            for (size_t i = 0; i < alloc_count; ++i) {
                new(&new_data[i]) obj_type_t(std::move(_data[i]));
                _data[i].~obj_type_t();
            }

            this->cleanup();
            _data = new_data;
        }

        auto
        cleanup()
            -> void {
            if (_data == nullptr) {
                return;
            }

            delete[](_data);
            _data = nullptr;
        }
    };
}}

#endif //DYNAMIC_ARRAY_HH

