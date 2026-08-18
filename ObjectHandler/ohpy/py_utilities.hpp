#ifndef __PY_OHP_UTILITIES_
#define __PY_OHP_UTILITIES_

#include "py_oh_utilities.hpp"

#define CATCH_PYDG_ERRORS(m)\
    catch (const std::exception &e) {\
        return return_error(m, e.what());\
    }\
    catch (...) {\
        return return_error(m, "unkown error type");\
    }


#endif //__PY_OHP_UTILITIES_
