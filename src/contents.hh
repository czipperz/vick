#ifndef HEADER_GUARD_CLASS_CONTENTS_H
#define HEADER_GUARD_CLASS_CONTENTS_H

#include <vector>
#include <string>
#include <memory>

#include "change.hh"
#include "mode.hh"

namespace vick {

/*!
 * \file contents.hh
 *
 * \brief Defines the class contents, which contains all the
 * information about the buffer.
 */

/*!
 * \brief Define \c move_t so that code can be more descriptive and
 * can change it from one place.
 */
using move_t = unsigned long;

/*!
 * \brief Define \c move_ts to be a signed version of \c move_t
 *
 * \see move_t
 */
using move_ts = long;

/*!
 * \class contents contents.hh "../../../src/contents.hh"
 *
 * \brief Defines all the information about the buffer.
 */
class contents {
public:
    std::map < char, std::function < boost::optional< std::shared_ptr<change> >
                                     (contents&, boost::optional<int>) > >
        normal_map /*!< \brief The contents buffer (file) specfic
                    * normal mode character mappings. */,
        insert_map /*!< \brief The contents buffer (file) specfic
                    * insert mode character mappings. */;

    /*!
     * \brief The type of file the buffer is.
     *
     * Default mode is fundamental;
     */
    mode* buffer_mode;

    /*!
     * \brief The literal contents of the buffer
     */
    std::vector<std::string> cont;

    /*!
     * \brief The list of changes to the buffer.  This is public so
     * that treed-undo (a la Emacs) can be implemented the same as
     * linear is.
     */
    std::vector<std::shared_ptr<change> > changes;

    /*!
     * \brief The current change the buffer is in
     */
    size_t changes_i = 0;

    move_t
        y = 0 /*!< \brief The y (vertical) position in the buffer. */,
        x = 0 /*!< \brief The x (horizontal) position in the buffer. */,
        desired_x = 0 /*!< \brief This will be set to the x value we
                       * want when you move to a different line but
                       * the line you move to is too short
                       *
                       * \see waiting_for_desired */,
        y_offset = 0 /*!< \brief The number of lines that are not
                      * displayed (off the top) */,
        max_y /*!< \brief The vertical height the buffer has been
               * allocated on the screen - [0, max_y) */,
        max_x /*!< \brief The horizontal width the buffer has been
               * allocated on the screen - [0, max_x) */;

    bool waiting_for_desired = false /*!< \brief Controls if the x
                                      * value will try to adjust to
                                      * desired_x
                                      *
                                      * \see desired_x */,
         refresh = true /*!< \brief Controls if the screen should
                         * refresh everytime something happens */,
         delete_mode = false /*!< \brief Controls if the private mode
                              * pointer variable will be deleted in the
                              * destructor */,
         is_inserting = false /*!< \brief Will be true if the user is
                               * currently inserting text into the
                               * buffer.  This will cause the
                               * print_contents method to not have
                               * undefined behavior if x is too
                               * large. */,
         windows_file_endings = false /*!< \brief If true, then when
                                       * saving, appends the byte 13 to
                                       * each line.  We use this to
                                       * maintain plugin consistency
                                       * across platforms.  (The buffer
                                       * is in no way affected by this
                                       * variable)
                                       */;

    explicit contents(std::vector<std::string> cont = std::vector<std::string>(),
                      mode* buffer_mode = &fundamental_mode);
    explicit contents(mode* buffer_mode);
    contents(move_t y, move_t x, mode* buffer_mode = &fundamental_mode);

    /*!
     * \brief Constructs this contents object as a copy of the other
     * contents object.
     *
     * This forces the private mode member to make a deep copy.
     */
    contents(const contents&);
    contents(contents&&) = default;

    /*!
     * \brief If delete_mode is true, then it will delete the private
     * mode pointer member.
     *
     * \see delete_mode
     */
    ~contents();

    /*!
     * \brief Constructs this contents object as a copy of the other
     * contents object.
     *
     * This forces the private mode member to make a deep copy.
     */
    contents& operator=(const contents&);
    contents& operator=(contents&&);

    /*!
     * \brief Calls the private mode member's `operator()` with
     * `*this` and the character given to this function.
     */
    bool operator()(char);

    /*!
     * \brief Updates the values of ``max_y`` and ``max_x``
     *
     * \see max_y
     * \see max_x
     */
    void refreshmaxyx();

    /*!
     * \brief Calls ``cont.push_back(str)``
     *
     * \see cont
     *
     * \param str The string to be put at the end of the vector of strings, cont
     */
    void push_back(const std::string& str);
};

}

#endif
