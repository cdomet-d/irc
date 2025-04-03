# Simplifying the checkers

Things we need to check:

- que le channel existe
- que l'utilisateur existe
- que la syntaxe est correcte, quelque qu'elle soit
- que l'utilisateur est sur le channel
- que l'utilisateur a les droits de ce qu'il essaye de faire

And then, command specific things that will be defined later. 

But the most repetitive tasks imply checking that things exists and that the syntax is correct.

## Proposal

We should have one checker for each command, each taking a `cmdSpec`. We already have those in `validator.hpp`.

Those specific checkers will be attributed in the command manager, and then proceed to call generic subcheckers.

# Generic checkers

Create two functions:

```cpp
/* define a template for all the maps */
template < typename MapType >
    bool check::exists(const cmdSpec &cmd, e_param type, const MapType &map) {
        // define some template related typename, could go in typedef.hpp
        typedef typename MapType::key_type key;
		typedef typename MapType::value_type val;

        typename MapType::const_iterator toFind = map.find(cmd[type]);

    }

```