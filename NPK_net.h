/*
Copyright 2022 Nikolaos Panagiotis Koukouras.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#if !defined NPK_NET_H_
    #define NPK_NET_H_

    #include "NPK_ds.h"
    #include <SDL2/SDL_net.h>

    // =================
    // NPK_net INTERFACE
    // =================

    #define NPK_array_to_packet(type, arr) NPK_array_to_packet_(sizeof(type), arr)
    #define NPK_string_to_packet(str) NPK_array_to_packet_(1, str)

    #define NPK_packet_to_array(type, p) NPK_packet_to_array_(sizeof(type), p)
    #define NPK_packet_to_string(p) NPK_packet_to_array_(1, p)

    UDPpacket NPK_array_to_packet_(int size, const NPK_array *arr);
    NPK_array NPK_packet_to_array_(int size, const UDPpacket *p);
    void NPK_packet_address(UDPpacket *p, const char *ip, int port);
#endif

#if defined NPK_NET_IMPL
    // ======================
    // NPK_net IMPLEMENTATION
    // ======================

    UDPpacket NPK_array_to_packet_(int size, const NPK_array *arr) {
        UDPpacket p;

        p.len = arr->len * size;
        p.maxlen = arr->maxlen * size;
        p.data = arr->data;

        return p;
    }

    NPK_array NPK_packet_to_array_(int size, const UDPpacket *p) {
        NPK_array arr;

        arr.len = p->len / size;
        arr.maxlen = p->maxlen / size;
        arr.data = p->data;

        return arr;
    }

    void NPK_packet_address(UDPpacket *p, const char *ip, int port) {
        IPaddress address;
        SDLNet_ResolveHost(&address, ip, port);

        p->address = address;
    }
#endif