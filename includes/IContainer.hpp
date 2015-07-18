#ifndef ICONTAINER_HPP
# define ICONTAINER_HPP

# include <Entity.hpp>

class IContainer
{
	public:
		virtual	~IContainer() {}
		virtual int				getCount() const = 0;
		virtual void			delUnit(int pos) = 0;
		virtual Entity*			getUnit(int) const = 0;
		virtual int				push(Entity*) = 0;
};

#endif
