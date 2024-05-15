//
// Created by Letícia Coelho on 15/05/2024.
//

#ifndef MAKE_UNIQUE_H
#define MAKE_UNIQUE_H

#include <memory>

namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif // MAKE_UNIQUE_H