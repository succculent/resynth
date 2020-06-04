/*
    Written by Elisabeth Vehling (vehling@usc.edu) for the project
    Neural Audio Resynth. A portion of code was referenced from the example
    on _____.com.
*/
#include <python/Python.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

//Filename and function name that we're calling
std::string FILENAME = "optimize";
std::string FUNCTION = "optimize";

//Test data: this will eventually be the synth parameters
double DATA[10] = {1.0, 2.0, 3.0, 4.0, 5.0};
int PARAMS = 5;


/*
    Embedding vs Extending: The difference is simple but a little confusing since they sound so similar. Embedding calls
    a Python interface from C, Extending calls a C routine from Python. For either process, keep in mind that any data being
    passed between the two needs to be converted from one language to another on both ends.

    Note: this program is written to support Python 2. For Python3 updates, several functions will need to be changed (al
    though not significantly). They should be backwards compatible if I'm not mistaken, so if you run into any errors
    let me know. I ran into significant set up errors with the versions of python on my laptop which I plan to address
    after I get this running, so hopefully I'll be able to figure out python3 support soon. 
*/
int main(int argc, char *argv[])
{
    /*
        Python objects for the name of the .py file, imported .py file,
        python function name, arguments to pass into the python function, and function return value
    */
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    int i;

    /*
        Convert the filename and function name from string to char* so that the python
        functions can use them. (It's much easier to change the global variable as a string
        than as a char* for testing). For deployment, remove the below part, global variables,
        and hard code the .py file name.
    */
	int len = FILENAME.size();
	char * fileName = new char[len + 1];
	std::copy(FILENAME.begin(), FILENAME.end(), fileName);
	fileName[len] = '\0';  

	len = FUNCTION.size();
	char *functionName = new char[len + 1];
	std::copy(FUNCTION.begin(), FUNCTION.end(), functionName);
	functionName[len] = '\0';  

    /*
        First we need to initialize a python interpreter! Py_Initialize() must be called 
        before using most Python/C API functions. If it is not initialized correctly,
        a fatal error should be thrown by Py_Initialize(), but if not, we check regardless.
    */
    Py_Initialize();
    if(!Py_IsInitialized()){
        throw "Fatal Error: Python interpreter was not initialized.";
        return 1;
    }

    /*
        Now we can start the process of running the function from our C++ code! Below, we tell
        the python interpreter we created that the .py file we want to execute is in the same 
        directory as this file, then create a python object from it. Finally, we import the module 
        and deallocate the object we used to contain the file name.
    */
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");
    pName = PyString_FromString(fileName);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);


    /*
        Attempt to access the module if it is viable. If not, the program terminates.
        If the module is accessible, we retreive the function from the module (python 
        file) and check if the function is accessible and callable.
    */
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, functionName);
        if (pFunc && PyCallable_Check(pFunc)) {

            //Convert data array to vector
            std::vector<int> data(std::begin(DATA), std::end(DATA));

            //Convert doubles from C -> Python
            pArgs = PyTuple_New(PARAMS);
            for(int i=0; i<data.size(); i++){
                pValue = PyLong_FromLong(data[i]);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert double to python float\n");
                    return 1;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }
        
            //Call the function with the converted arguments
            pValue = PyObject_CallObject(pFunc, pArgs);
            if(pValue == NULL) {
                throw "Return value from optimization was invalid. ";
                return 1;
            }

            //-------------------
            // PyObject* pList;
            // PyObject* pListItem;

            // std::vector<double> ret;
            // if (pValue != NULL)
            // {
            //     int py_list_size = PyList_Size(pValue);
            //     for(Py_ssize_t i = 0; i < py_list_size; ++i)
            //     {
            //         pList = PyList_GetItem(pValue, i);
            //         std::cout << PyLong_AsDouble(pList) << std::endl;
            //         // ret.push_back((double)PyLong_AsLong(pList));
            //         // if(PyLong_Check(pList))
            //         // {
            //         //     int pyNumber = PyLong_AsLong(pList);
            //         //     ret.push_back(pyNumber);
            //         // }
            //     }
            // }
            //------------------

            //Prints the result of the function call
            if (pValue != NULL) {
                PyObject_Print(pValue, stdout, 0); 
                Py_DECREF(pValue);
                Py_DECREF(pArgs);
            }
            //The function call returned NULL
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Optimization call failed\n");
                return 1;
            }
        }
        //The function was not able to be loaded
        else {
            if (PyErr_Occurred()){
                PyErr_Print();
            }
            fprintf(stderr, "Could not find function \"%s\". Check to make sure function exists and is spelled correctly.\n", argv[2]);
        }

        //Deallocate the function/modules
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\": Make sure file exists and does include .py extension.\n", argv[1]);
        return 1;
    }

    //Deallocate memory from python interpeter and any other variables created
    try{
        Py_Finalize();
    }
    catch(int e){
        return 120;
    }
    delete[] fileName;
    delete[] functionName;

    return 0;
}
