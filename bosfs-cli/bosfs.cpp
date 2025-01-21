//
// Created by Tureb on 21.01.2025.
//

#include "bosfs.h"

#include "cli/loopscheduler.h"
#include "cli/clilocalsession.h"


int main(int argc, char **argv) {

    auto root = std::make_unique<cli::Menu>("bosfs");

    root->Insert("test",
                 [](std::ostream &out) { out << "Test command executed!" << std::endl; },
                 "Test the cli lib");

    cli::Cli cli(std::move(root)); //move root for performance

    cli.ExitAction([](std::ostream &out) {
        out << "BOSFS by Ture Bentzin" << std::endl;
    });


    cli::LoopScheduler scheduler;
    cli::CliLocalTerminalSession session(cli, scheduler, std::cout);

    session.ExitAction([&scheduler](std::ostream &out) {
        scheduler.Stop();
    });

    scheduler.Run();

}