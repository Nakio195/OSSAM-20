#include "System/Commands/Command.h"
#include <iostream>

Command::Command() : action(), category(Category::Uninitialized), id(0)
{
}

CommandQueue::CommandQueue()
{

}

void CommandQueue::push(const Command& command)
{
    mQueue.push(command);
}

Command CommandQueue::pop()
{
    Command command = mQueue.front();
    mQueue.pop();

    return command;
}

bool CommandQueue::isEmpty()
{
    return mQueue.empty();
}
