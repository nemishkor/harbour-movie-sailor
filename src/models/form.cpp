#include "form.h"

Form::Form()
{

}

bool Form::isValid() const
{
    return true;
}

bool Form::isDirty() const
{
    return dirty;
}

void Form::setDirty(bool newDirty)
{
    dirty = newDirty;
}
