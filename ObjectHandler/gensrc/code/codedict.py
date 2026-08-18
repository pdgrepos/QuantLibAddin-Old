
##########################################################################
# code for Excel
##########################################################################

code11 = '''\
        std::string %(name)sCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*%(name)s), "%(name)s", %(defaultValue)s);\n'''

code12 = '''\
        %(nativeType)s %(name)sCpp = ObjectHandler::convert2<%(nativeType)s>(
            ObjectHandler::ConvertOper(*%(name)s), "%(name)s", %(defaultValue)s);\n'''

code13 = '''\
        std::vector<%(nativeType)s> %(name)sCpp =
            ObjectHandler::operToVector<%(nativeType)s>(
                *%(name)s, "%(name)s");\n'''

code14 = '''\
        std::vector<long> %(name)sCpp =
            ObjectHandler::operToVector<long>(
                *%(name)s, "%(name)s");\n'''

code15 = '''\
        std::vector<double> %(name)sCpp =
            ObjectHandler::operToVector<double>(
                *%(name)s, "%(name)s");\n'''

code16 = '''\
        std::vector<std::string> %(name)sCpp =
            ObjectHandler::operToVector<std::string>(
                *%(name)s, "%(name)s");\n'''

code17 = '''\
        std::vector<boost::any> %(name)sCpp =
            ObjectHandler::operToVector<boost::any>(
                *%(name)s, "%(name)s");\n'''

code18 = '''\
        std::vector<std::vector<%(type)s> > %(name)sCpp =
            ObjectHandler::operToMatrix<%(type)s>(*%(name)s);\n'''

code19 = '''\
        std::vector<std::vector<long> > %(name)sCpp =
            ObjectHandler::fpToMatrix<long>(*%(name)s);\n'''

code20 = '''\
        std::vector<std::vector<double> > %(name)sCpp =
            ObjectHandler::fpToMatrix<double>(*%(name)s);\n'''

code21a = '''\
        std::vector<std::vector<std::string> > %(name)sCpp =
            ObjectHandler::operToMatrix<std::string>(*%(name)s);\n'''

code21b = '''\
        std::vector<std::vector<boost::any> > %(name)sCpp =
            ObjectHandler::operToMatrix<boost::any>(*%(name)s);\n'''

code25 = '''\
        %(type)s %(name)sLib = ObjectHandler::convert2<%(type)s>(
            ObjectHandler::ConvertOper(%(name)s), "%(name)s", %(defaultValue)s);\n'''

code26 = '''\
        %(type)s %(name)sLib = ObjectHandler::convert2<%(type)s>(
            ObjectHandler::ConvertOper(*%(name)s), "%(name)s", %(defaultValue)s);\n'''

code31 = '''\
        std::vector<%(type)s> %(name)sLib =
            ObjectHandler::operToVectorLibrary<%(type)s>(
            *%(name)s);\n'''

code32 = '''\
        std::vector<%(type)s> %(name)sLib =
            ObjectHandler::operToVector<%(type)s>(
                *%(name)s, "%(name)s");\n'''

code34 = '''\
        %(type)s %(name)sEnum =
            %(namespaceObjects)s::Create<%(type)s>()(%(name)s);\n'''

code35 = '''\
        std::vector<%(type)s> %(name)sEnum =
            ObjectHandler::operToVectorEnum<%(type)s,
            %(namespaceObjects)s::Create<%(type)s> >(*%(name)s);\n'''

code36a = '''\
        OH_GET_OBJECT(%(name)sObj, %(name)s, %(type)s)\n'''

code37 = '''\
        std::vector<boost::shared_ptr<%(namespaceObjects)s::%(classname)s> > %(name)sObj =
            ObjectHandler::getObjectVector<%(namespaceObjects)s::%(classname)s>(%(name)sCpp);\n'''

code38 = '''\
        OH_GET_REFERENCE(%(name)sLibObj, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s)\n'''

code39 = '''\
        OH_GET_REFERENCE_DEFAULT(%(name)sLibObj, %(name)sCpp,
            %(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s)\n'''

code42 = '''\
        std::vector<boost::shared_ptr<%(namespaceLibrary)s::%(classname)s> > %(name)sLibObj =
            ObjectHandler::operToObjectVector<%(namespaceLibrary)s::%(classname)s, %(namespaceObjects)s::%(classname)s>(
            *%(name)s);\n'''

code44 = '''\
        OH_GET_OBJECT(%(name)sTemp, %(name)s, ObjectHandler::Object)
        %(namespaceLibrary)s::RelinkableHandle<%(namespaceLibrary)s::%(classname)s> %(name)sLibObj =
            %(namespaceObjects)s::CoerceHandle<
                %(namespaceObjects)s::%(classname)s,
                %(namespaceLibrary)s::%(classname)s>()(
                    %(name)sTemp);\n'''

code45b = '''\
        OH_GET_OBJECT(%(name)sTemp, %(name)s, ObjectHandler::Object)
        boost::shared_ptr<%(namespaceLibrary)s::%(classname)s> %(name)sLibObj =
            %(namespaceObjects)s::CoerceToObject<
                %(namespaceObjects)s::%(classname)s,
                %(namespaceLibrary)s::%(classname)s>()(
                    %(name)sTemp);\n'''

code48 = '''\
        OH_GET_UNDERLYING(%(name)sLibObj, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s)\n'''

code50 = '''\
        std::vector<std::vector<%(namespaceLibrary)s::RelinkableHandle<%(namespaceLibrary)s::%(classname)s> > > %(name)sLibObj =
            ObjectHandler::operToMatrixHandle<%(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s>(*%(name)s);\n'''

code51 = '''\
std::vector<std::vector<std::string> > returnValue = '''

code52 = '''\
std::vector<std::vector<%(type)s> > returnValue = '''

code53 = '''\
std::vector<std::vector<boost::any> > returnValue = '''

code54 = '''\
            %(name)sLib.begin(),
            %(name)sLib.end()'''

code55 = '''\
            %(name)sCpp.begin(),
            %(name)sCpp.end()'''

code58 = '''\
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;'''

code59 = '''\
        static OPER xRet;
        ObjectHandler::%(tensorRank)sToOper(returnValue, xRet);
        return &xRet;'''

code60 = '''\
        return &returnValue;'''

code64 = '''\
        static OPER xRet;
        ObjectHandler::%(tensorRank)sToOper(returnValue, xRet);
        return &xRet;'''

#code65 = '''\
#        static OPER xRet;
#        ObjectHandler::%(tensorRank)sToOper(returnValue, xRet);
#        return &xRet;'''

code65 = '''\
        std::string %(name)sStrip = ObjectHandler::ObjectXL::getStub(%(name)s);'''

##########################################################################
# code for ValueObjects
##########################################################################

code66 = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            return %(name)s_;\n'''

code66a = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            return %(name)s_;\n'''

code67a = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = value;\n'''

code67b = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::convert2<std::string>(value);\n'''

code67c = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::convert2<%(nativeType)s>(value);\n'''

code67d = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);\n'''

code67e = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);\n'''

code67f = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::vector::convert2<%(nativeType)s>(value, nameUpper);\n'''

code67g = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);\n'''

code67h = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::matrix::convert2<std::string>(value, nameUpper);\n'''

code67i = '''\
        else if(strcmp(nameUpper.c_str(), "%(nameUpper)s")==0)
            %(name)s_ = ObjectHandler::matrix::convert2<%(nativeType)s>(value, nameUpper);\n'''

code69 = '''\
            processPrecedentID(%(name)s);'''

code70 = '''\
            for (std::vector<std::string>::const_iterator i = %(name)s.begin();
                    i != %(name)s.end(); ++i)
                processPrecedentID(*i);'''


##########################################################################
# code for Python
##########################################################################

codePy1 = '''\
        const %(nativeType)s& %(name)s = convertValue<%(nativeType)s>(objects[%(parIndex)s]);'''

codePy1_Opt = '''\
        const boost::optional<%(nativeType)s>& %(name)s = convertOptionalValue<%(nativeType)s>(objects[%(parIndex)s]);'''

codePy2_Opt = '''\
        const %(nativeType)s& %(name)s = convertOptionalValue<%(nativeType)s>(objects[%(parIndex)s], %(defaultValue)s);'''

codePy1_1 = '''\
        const std::string& %(name)s = convertValue<std::string>(objects[%(parIndex)s]);'''

codePy2 = '''\
        const std::vector<%(nativeType)s>& %(name)s = convertVector<%(nativeType)s>(objects[%(parIndex)s]);'''

codePy2_1 = '''\
        const std::vector<std::string>& %(name)s = convertVector<std::string>(objects[%(parIndex)s]);'''

codePy2_2 = '''\
        const std::vector<ObjectHandler::property_t>& %(name)s = convertVector<ObjectHandler::property_t>(objects[%(parIndex)s]);'''

codePy2_3 = '''\
        const std::vector<%(type)s>& %(name)s = convertVector<%(type)s>(objects[%(parIndex)s]);'''

codePy3 = '''\
        const std::vector<std::vector<%(nativeType)s> >& %(name)s = convertVector<std::vector<%(nativeType)s> >(objects[%(parIndex)s]);'''

codePy3_1 = '''\
        const std::vector<std::vector<std::string> >& %(name)s = convertVector<std::vector<std::string> >(objects[%(parIndex)s]);'''

codePy3_2 = '''\
        const std::vector<std::vector<ObjectHandler::property_t> >& %(name)s = convertVector<std::vector<ObjectHandler::property_t> >(objects[%(parIndex)s]);'''

codePy4 = '''\
        std::vector<%(type)s> %(nameConverted)s = PdgLibAddin::convertVector<long, Date>(%(name)s);\n
        std::vector<ObjectHandler::property_t> %(name)sCpp = pdg::convertDatesToProperty(%(name)s);\n'''

codePy5 = '''\
        %(type)s %(nameConverted)s =
            LocalEnumRegistry<%(type)s>::instance().parse(%(name)s);\n'''

codePy6 = '''\
        %(type)s %(nameConverted)s(%(name)s);\n'''

codePy7 = '''\
        Matrix %(nameConverted)s(credit::convertMatrix(%(name)s));\n'''

codePy37M = '''\
        std::vector<boost::shared_ptr<%(nameSpace)s::%(classname)s> > %(nameConverted)s =
            ObjectHandler::getLibraryObjectVector<%(namespaceObjects)s::%(classname)s, %(nameSpace)s::%(classname)s>(%(name)s);\n'''

codePy37NullXL = '''\
        std::vector<boost::shared_ptr<%(classname)s> > %(nameConverted)s =
            ObjectHandler::getLibraryObjectVector<%(namespaceObjects)s::%(classname)sAddin, %(classname)s>(%(name)s);\n'''

code35cpp = '''\
        std::vector<%(type)s> %(nameConverted)s =
            ObjectHandler::vectorStringToEnum<%(type)s>(%(name)s, "%(name)s");\n'''

code39p = '''\
        OH_GET_REFERENCE_DEFAULT(%(nameConverted)s, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s)\n'''

code38M = '''\
        OH_GET_REFERENCE(%(nameConverted)s, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(nameSpace)s::%(classname)s)\n'''

code48c = '''\
        OH_GET_UNDERLYING(%(nameConverted)s, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(nameSpace)s::%(classname)s)\n'''

code49c = '''\
        OH_GET_UNDERLYING_NONCONST(%(nameConverted)s, %(name)s,
            %(namespaceObjects)s::%(classname)s, %(nameSpace)s::%(classname)s)\n'''

code37ecpp = '''\
        std::vector<std::vector<boost::shared_ptr<%(namespaceLibrary)s::%(classname)s> > > %(nameConverted)s =
            ObjectHandler::getLibraryObjectMatrix<%(namespaceObjects)s::%(classname)s, %(namespaceLibrary)s::%(classname)s>(%(name)s);\n'''

code37ecppM = '''\
        std::vector<std::vector<boost::shared_ptr<%(nameSpace)s::%(classname)s> > > %(nameConverted)s =
            ObjectHandler::getLibraryObjectMatrix<%(namespaceObjects)s::%(classname)s, %(nameSpace)s::%(classname)s>(%(name)s);\n'''

codePy27 = '''\
        %(type)s %(nameConverted)s = %(name)s;\n'''

codePy27_Opt = '''\
        %(type)s %(nameConverted)s = %(name)s.has_value() ? %(type)s(*%(name)s) : %(defaultValue)s;\n '''

codePy31 = '''\
        std::vector<%(type)s> %(nameConverted)s = %(name)s;\n '''

code36 = '''\
        OH_GET_OBJECT(%(nameConverted)s, %(name)s, %(type)s)\n'''

code160 = '''\
        std::vector<boost::shared_ptr<%(namespaceObjects)s::%(classname)s> > %(nameConverted)s =
            ObjectHandler::getObjectVector<%(namespaceObjects)s::%(classname)s>(%(name)s);\n'''

##########################################################################
# code common to mutiple addins
##########################################################################

wrap1 = '''
        // convert input datatypes to C++ datatypes

%s'''

wrap2 = '''
        // convert input datatypes to QuantLib datatypes

%s'''

wrap3 = '''
        // convert input datatypes to QuantLib enumerated datatypes

%s'''

wrap4 = '''
        // convert input datatypes to Object references

%s'''

wrap5 = '''
        // convert object IDs into library objects

%s'''

wrap6 = '''
        // perform data conversion for return value of function

%s'''

