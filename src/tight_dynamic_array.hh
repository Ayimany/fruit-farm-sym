#ifndef DYNAMIC_ARRAY_HH
#define DYNAMIC_ARRAY_HH

#include <cstdlib>
#include <cstring>
#include <functional>
#include <stdexcept>

namespace fmk {
    // Use of vectors is forbidden, so we will design our own array
    // I assume smart pointers are also not allowed, so I will use raw pointers

    /**
     * Represents a dynamic array that can only allocate as many elements as it
     * contains.
     * @tparam obj_type_t The type of element to hold.
     */
    template <typename obj_type_t>
    class tight_dynamic_array {
    public:
        using iterator   = obj_type_t *;
        using iterator_c = const obj_type_t *;

        explicit
        tight_dynamic_array()
            : _size(0) {
            _data = static_cast<obj_type_t *>((calloc(0, sizeof(obj_type_t))));
            if (_data == nullptr) {
                throw std::runtime_error {
                    "Could not allocate memory for a dynamic array"
                };
            }
        }

        ~tight_dynamic_array() {
            if (_data != nullptr) {
                free(_data);
                _data = nullptr;
            }
        }

        [[nodiscard]] auto
        get(
            size_t index
        )
            -> obj_type_t & {
            if (index > _size) {
                free(_data);
                _data = nullptr;

                throw std::runtime_error {
                    "Index " + std::to_string(index) +
                    " out of bounds for size " + std::to_string(_size)
                };
            }

            return _data[index];
        }

        template <typename... arg_types_t>
        auto
        emplace(
            arg_types_t &&... args
        )
            -> void {
            resize(_size + 1);
            _data[_size++] = obj_type_t { args... };
        }

        auto
        remove(
            const size_t index
        )
            -> void {
            if (index >= _size) {
                free(_data);
                _data = nullptr;

                throw std::runtime_error {
                    "Index " + std::to_string(index) +
                    " out of bounds for size " + std::to_string(_size)
                };
            }

            if (index != _size - 1) {
                memcpy(
                    _data + index,
                    _data + index + 1,
                    (_size - index) * sizeof(obj_type_t)
                );
            }

            resize(--_size);
        }

        [[nodiscard]] auto
        size() const noexcept
            -> size_t {
            return this->_size;
        }

        auto
        for_each(
            std::function<void(obj_type_t &obj)> func
        )
            -> void {
            for (size_t i = 0; i < this->_size; i++) {
                func(_data[i]);
            }
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
            return get(index);
        }

    private:
        obj_type_t *_data;
        size_t      _size;

        auto
        resize(
            const size_t alloc_count
        )
            -> void {
            obj_type_t *reallocated_data;

            if (alloc_count != 0) {
                reallocated_data = static_cast<obj_type_t *>(realloc(
                    _data,
                    alloc_count * sizeof(obj_type_t)
                ));
            } else {
                reallocated_data = static_cast<obj_type_t *>(calloc(
                    0,
                    sizeof(obj_type_t)
                ));
            }

            if (reallocated_data == nullptr) {
                free(_data);
                _data = nullptr;

                throw std::runtime_error {
                    "Could not reallocate memory for dynamic array growth"
                };
            }

            _data = reallocated_data;
        }
    };
}

#endif //DYNAMIC_ARRAY_HH

