

#include <ctime>

#include "token.h"

void easter_egg_splash() {
    const auto msg = abs(random() % 21);

    switch (msg) {
        case 0:
            printf("C-Block blocking its way in! * smash intro sounds *\n"); break;
        case 1:
            printf("Also try JMC!"); break;
        case 2:
            printf("Huzzah!"); break;
        case 3:
            printf("Did you know that C-Block stands for \"Command Block\"? :]"); break;
        case 4:
            printf("Days since last mcfunction language: 0"); break;
        case 5:
            printf("C rulez!"); break;
        case 6:
            printf("NBT shall set you free (definitively not boq - 2026)"); break;
        case 7:
            printf("Haha... world go boom-boom on 2038"); break;
        case 8:
            printf("We got Silksong before GTA IV"); break;
        case 9:
            printf("Made for Minelifts!"); break;
        case 10:
            printf("Rocking its oververbose syntax since 2026!"); break;
        case 11:
            printf("Try 'sudo rm -rf /' It will do something funny ;]\n\n... if you're on windoofs, you're sucker!"); break;
        case 12:
            printf("i use arch linux btw"); break;
        case 13:
            printf("ngl datapacks are overrated, who needs them? * laughs *"); break;
        case 14:
            printf("Never trust the sheep riding a minecart that rides another minecart. It will cheat, it will lie & it will do anything in its power to convince you to piss off"); break;
        case 15:
            printf("Trust vdv!"); break;
        case 16:
            printf("Not rusty enough"); break;
        case 17:
            printf("WOOOOOOOOOOOOHOOOOOOOOOOOOOOOOOOOOO!!!!! IT'S C-BLOCK SHOWTIME!"); break;
        case 18:
            printf("Talk more in #no-balls-talk!"); break;
        case 19:
            printf("Ptsss! Where's the icy lemon?"); break;
        case 20:
            printf("Made in brain[nsfw word]!"); break;
        case 21:
            printf("boq! give us 'math'!"); break;
        default:
            printf("Huh... you should never have seen this?");
    }
}

void easter_egg_err_msg() {
    const auto msg = abs(random() % 16);
    switch (msg) {
        case 0:
            printf("no compiling? ):"); break;
        case 1:
            printf("Ouch! I think I slipped..."); break;
        case 2:
            printf("Have you tried turning it off & on?"); break;
        case 3:
            printf("Uh-hu-huhu! You didn't say the magic word!"); break;
        case 4:
            printf("Forgetting semicolons since 2026 (you!)"); break;
        case 5:
            printf("Back to the beginnings, ain't ya?"); break;
        default:
    }
}

int main() {
    C_BLOCK::c_stream file("example.txt");

    file.berserk_along_whitespaces_and_comments();
    C_BLOCK::token token_example(file);
    return 0;
}

