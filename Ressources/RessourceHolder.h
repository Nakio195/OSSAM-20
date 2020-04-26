#ifndef RESSOURCEHOLDER_H
#define RESSOURCEHOLDER_H

#include <memory>
#include <map>
#include <assert.h>


template <typename Ressource, typename Identifier>
class RessourceHolder
{
    public:
        RessourceHolder();

        void load(Identifier id, const std::string& filename);
        template <typename Parameter>
        void load(Identifier id, const std::string& filename, const Parameter& secondParameter);

        Ressource& get(Identifier id);
        const Ressource& get(Identifier id) const;

    private:
        std::map<Identifier, std::unique_ptr<Ressource>> mRessourceMap;

};

#include "RessourceHolder.inl"

#endif // RESSOURCEHOLDER_H
