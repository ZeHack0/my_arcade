/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** DLLoader
*/

#pragma once
#include <dlfcn.h>
#include <string>
#include <stdexcept>

namespace arcade {

    class DLLoader {

        public:
            DLLoader(const std::string& path) {
                _handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!_handle)
                    throw std::runtime_error(dlerror());
            }
            ~DLLoader() {
                if (_handle)
                    dlclose(_handle);
            }

            template <typename T>
            T *getInstance() {
                auto *(*creator)() = (T *(*)())dlsym(_handle, "instance");

                if (!creator)
                    throw std::runtime_error(dlerror());
                return creator();
            }

        private:
            void *_handle;

    };

}
