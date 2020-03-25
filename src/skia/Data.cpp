#include <pybind11/pybind11.h>
#include <skia.h>

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, sk_sp<T>);

void initData(py::module &m) {
py::class_<SkData, sk_sp<SkData>>(m, "Data", py::buffer_protocol())
    .def_buffer([](SkData &d) -> py::buffer_info {
        return py::buffer_info(
            d.writable_data(),
            sizeof(uint8_t),
            py::format_descriptor<uint8_t>::format(),
            1,
            { d.size() },
            { sizeof(uint8_t) }
        );
    })
    .def("size", &SkData::size, "Returns the number of bytes stored.")
    .def("isEmpty", &SkData::isEmpty)
    .def("data", &SkData::data, "Returns the ptr to the data.",
        py::return_value_policy::reference)
    // .def("bytes", &SkData::bytes, return_value_policy::reference)
    .def("writable_data", &SkData::writable_data, "USE WITH CAUTION.",
        py::return_value_policy::reference)
    .def("copyRange", &SkData::copyRange,
        "Helper to copy a range of the data into a caller-provided buffer.")
    .def("equals", &SkData::equals, "Returns true if these two objects have the"
        " same length and contents, effectively returning 0 == memcmp(...)")
    .def("unique", &SkData::unique)
    .def("ref", &SkData::ref)
    .def("unref", &SkData::unref)
    .def("deref", &SkData::deref)
    .def("refCntGreaterThan", &SkData::refCntGreaterThan)
    .def_static("MakeWithCopy", &SkData::MakeWithCopy,
        "Create a new dataref by copying the specified data.")
    .def_static("MakeUninitialized", &SkData::MakeUninitialized,
        "Create a new data with uninitialized contents.")
    .def_static("MakeWithCString", &SkData::MakeWithCString,
        "Create a new dataref by copying the specified c-string (a "
        "null-terminated array of bytes).")
    // .def_static("MakeWithProc", &SkData::MakeWithProc,
    //     "Create a new dataref, taking the ptr as is, and using the "
    //     "releaseproc to free it.")
    .def_static("MakeWithoutCopy", &SkData::MakeWithoutCopy,
        "Call this when the data parameter is already const and will outlive "
        "the lifetime of the SkData.")
    .def_static("MakeFromMalloc", &SkData::MakeFromMalloc,
        "Create a new dataref from a pointer allocated by malloc.")
    .def_static("MakeFromFileName", &SkData::MakeFromFileName,
        "Create a new dataref the file with the specified path.")
    .def_static("MakeFromFILE", &SkData::MakeFromFILE,
        "Create a new dataref from a stdio FILE.")
    .def_static("MakeFromFD", &SkData::MakeFromFD,
        "Create a new dataref from a file descriptor.")
    // .def_static("MakeFromStream", &SkData::MakeFromStream, "Attempt to read"
    //      " size bytes into a SkData.")
    .def_static("MakeSubset", &SkData::MakeSubset,
        "Create a new dataref using a subset of the data in the specified src "
        "dataref.")
    .def_static("MakeEmpty", &SkData::MakeEmpty,
        "Returns a new empty dataref (or a reference to a shared empty "
        "dataref).")
    ;
}