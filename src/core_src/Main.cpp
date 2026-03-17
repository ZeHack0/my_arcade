/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Main
*/

#include <iostream>
#include <vector>
#include <dlfcn.h>

int main(int ac, char **av) {

    std::vector<void*> handles;
    std::vector<void (*)()> entries;
    (void)ac;

    for (int i = 1; av[i] != nullptr; i++) {
        void *h = dlopen(av[i], RTLD_LAZY);
        if (h) {
            handles.push_back(h);
            void (*f)() = (void (*)())dlsym(h, "entryPoint");
            if (f) entries.push_back(f);
        }
    }

    for (auto entry : entries) {
        entry();
    }

    for (auto h : handles) {
        dlclose(h);
    }

    return 0;

}
