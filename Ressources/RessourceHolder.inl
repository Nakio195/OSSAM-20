#include "Ressources/RessourceHolder.h"
#include <iostream>


template <typename Ressource, typename Identifier>
RessourceHolder<Ressource, Identifier>::RessourceHolder()
{

}

template <typename Ressource, typename Identifier>
void RessourceHolder<Ressource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Ressource> ressource(new Ressource);

    if(!ressource->loadFromFile(filename))
        throw std::runtime_error("Failed to load : " + filename);

    auto inserted = mRessourceMap.insert(std::make_pair(id, std::move(ressource)));
    assert(inserted.second);
}

template <typename Ressource, typename Identifier>
template <typename Parameter>
void RessourceHolder<Ressource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParameter)
{
    std::unique_ptr<Ressource> ressource(new Ressource);

    if(!ressource->loadFromFile(filename, secondParameter))
        throw std::runtime_error("Failed to load : " + filename);

    auto inserted = mRessourceMap.insert(std::make_pair(id, std::move(ressource)));
    assert(inserted.second);
}


template <typename Ressource, typename Identifier>
Ressource& RessourceHolder<Ressource, Identifier>::get(Identifier id)
{
    auto found = mRessourceMap.find(id);
    assert(found != mRessourceMap.end());

    return *found->second;
}

template <typename Ressource, typename Identifier>
const Ressource& RessourceHolder<Ressource, Identifier>::get(Identifier id) const
{
    auto found = mRessourceMap.find(id);

    if(found == mRessourceMap.end())
        std::cerr << "Unable to locate ressource " << static_cast<int>(id) << std::endl;

    assert(found != mRessourceMap.end());

    return *found->second;
}
