#include "inputconfigwriter.h"

#include <iomanip>
#include <assert.h>

#include "inputmapping.h"
#include "ui/actionkeymapping.h"


InputConfigWriter::InputConfigWriter(const std::string& file):
    m_file()
{
    m_file.open(file, std::ios::out);
    assert(m_file.is_open());
    if (m_file.is_open()) {
        m_file << "[input]" << std::endl;
    } else {
        glow::warning("InputConfigWriter: cant open file %;", file);
    }

}

InputConfigWriter::~InputConfigWriter() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

void InputConfigWriter::write(ActionKeyMapping& mapping) {
    if (m_file.is_open()) {
        write(mapping.mappingName(InputClass::Primary), mapping.mapping(InputClass::Primary));
        write(mapping.mappingName(InputClass::Secondary), mapping.mapping(InputClass::Secondary));
    }
}

void InputConfigWriter::write(std::string name, const InputMapping& mapping) {
    name.erase(name.begin(), name.begin() + 6); // remove "input."
    m_file << name << " = InputMapping(";
    m_file << std::setprecision(2);
    m_file << static_cast<int>(mapping.type()) << ",";
    m_file << mapping.index() << ",";
    m_file << mapping.maxValue() << ",";
    m_file << mapping.idleValue() << ")" << std::endl;
}

