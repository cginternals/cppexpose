
namespace cppexpose
{


template <typename Type>
Type AbstractProperty::option(const std::string & key, const Type & defaultValue) const
{
    return option(key).value<Type>(defaultValue);
}


} // namespace cppexpose
