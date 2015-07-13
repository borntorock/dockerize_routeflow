#ifndef INTERFACE_HH
#define INTERFACE_HH

#include "converter.h"
#include "types/IPAddress.h"
#include "types/MACAddress.h"

class Interface {
    public:
        uint32_t port;
        string name;
        std::vector<IPAddress> addresses;
        MACAddress hwaddress;
        bool active;
        bool physical;
        uint32_t vlan;

        Interface() {
            this->active = false;
            this->physical = false;
            this->port = 0;
            this->vlan = 0;
        }

        Interface& operator=(const Interface& other) {
            if (this != &other) {
                this->port = other.port;
                this->name = other.name;
                this->addresses = other.addresses;
                this->hwaddress = other.hwaddress;
                this->active = other.active;
                this->physical = other.physical;
                this->vlan = other.vlan;
            }
            return *this;
        }

        bool operator==(const Interface& other) const {
            return
                (this->port == other.port) &&
                (this->name == other.name) &&
                (this->addresses == other.addresses) && 
                (this->hwaddress == other.hwaddress) &&
                (this->active == other.active) &&
                (this->physical == other.physical) &&
                (this->vlan == other.vlan);
        }
        
        string toString() {
            string description = this->name;
            description += " port: " + to_string<uint32_t>(this->port);
            description += " physical: " + to_string<bool>(this->physical);
            description += " active: " + to_string<bool>(this->active);
            description += " vlan: " + to_string<uint32_t>(this->vlan);
            description += " hwaddress: " + this->hwaddress.toString();
            description += " addresses:";
            for (std::vector<IPAddress>::iterator it = this->addresses.begin();
                 it != this->addresses.end();
                 ++it) {
                description += " " + it->toString();
            }
            return description;
        }
};

/**
 * Abstract class InterfaceMap. Subclasses can implement this functionality
 * to provide access to Interfaces by name.
 */
class InterfaceMap {
    public:
        /**
         * Searches for an interface matching the given name. If it exists,
         * the interface is copied into *dst.
         *
         * Returns true on success, or false on failure.
         */
        virtual bool findInterface(const char *ifName, Interface *dst) = 0;
};

#endif /* INTERFACE_HH */
