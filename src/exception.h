/**
 * @file
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

namespace retrocombinator
{
    /** Basic class to represent exceptions.
     *  Stores the error message corresponding to when it was raised.
     */
    class Exception
    {
    private:
        /// A helpful diagnostic message of why this exception was thrown
        const std::string error_msg;

    public:
        /** Basic constructor for an exception that is to be thrown.
         *  \param error_msg \copydoc Exception::error_msg
         */
        Exception(std::string error_msg) :
            error_msg(error_msg) {}

        /** What was the error message for this exception?
         */
        std::string what() const { return error_msg; }
    };
}

#endif //EXCEPTION_H
