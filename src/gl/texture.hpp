#pragma once
#include "types.hpp"
#include "std_ext/view.hpp"

namespace gl {
    class texture {
        gl::uint id;
        public:
            inline texture(gl::uint width, gl::uint height, std::ext::view<gl::ubyte> data) {
                glGenTextures(1, &id);

                bind();

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.data());

                // Nice filtering, or ...
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

                // ... ugly trilinear filtering ...
                // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                // ... which requires mipmaps. Generate them automatically.
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            texture(const texture&) = delete;
            texture& operator=(const texture&) = delete;

            inline void bind() const {
                glBindTexture(GL_TEXTURE_2D, id);
            }
    };
}