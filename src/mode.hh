#ifndef HEADER_GUARD_MODE_H
#define HEADER_GUARD_MODE_H

#include <functional>
#include <map>
#include <string>
#include <boost/optional.hpp>
#include <memory>

#include "change.hh"

namespace vick {

/*!
 * \file mode.hh
 * \brief Declares ``global_normal_map``, ``global_insert_map``, and the mode class
 */

class contents;

extern std::map < char, std::function < boost::optional< std::shared_ptr<change> >
                                            (contents&, boost::optional<int>) > >
    global_normal_map /*!< \brief The keybinding to be used in "normal
                       * mode"
                       *
                       * The keybinding to be used while in "normal
                       * mode", the mode where the user doesn't insert
                       * text but rather moves around and modifies the
                       * structure of the document */,
    global_insert_map /*!< \brief The keybinding to be used while in
                       * "insert mode"
                       *
                       * The keybinding to be used while in "insert
                       * mode", the mode where the user inserts text
                       * into the buffer */;

/*!
 * \class mode mode.hh "../../../src/mode.hh"
 *
 * \brief Declares a method to handle key strokes and possibly
 * interpret them as commands.
 */
class mode {
private:
    std::string name;
    int unique_id;
    std::shared_ptr<std::map<char, std::function<boost::optional<std::shared_ptr<change> >
                                                 (contents&, boost::optional<int>)> > >
        normal_map, insert_map;

public:
    /*!
     * \brief Constructs a managed mode object
     * \param name Do not put "mode" in your name, for example input
     * "Fundamental".
     */
    mode(const std::string& name);
    mode(const mode&) = default;
    mode(mode&&) = default;

    /*!
     * \brief Checks the contents specific map, the mode specific map,
     * then the global map for a binding that matches the character
     * given.
     */
    bool operator()(contents&, char) const;

    /*!
     * \brief Returns the name associated with this mode object.
     */
    const std::string& get_name() const;

    /*!
     * \brief Compares the unique identifiers
     */
    bool operator==(const mode&) const;
    /*!
     * \brief Compares the unique identifiers
     */
    bool operator!=(const mode&) const;

    /*!
     * \brief Binds the character given to the function in the mode
     * specific normal map.
     */
    void add_to_mode_normal_map(char, std::function<boost::optional<std::shared_ptr<change> >
                                                    (contents&, boost::optional<int>)>);

    /*!
     * \brief Binds the character given to the function in the mode
     * specific insert map.
     */
    void add_to_mode_insert_map(char, std::function<boost::optional<std::shared_ptr<change> >
                                                    (contents&, boost::optional<int>)>);
};

/*!
 * The basic file mode
 */
extern mode fundamental_mode; // use global maps only

}

#endif
