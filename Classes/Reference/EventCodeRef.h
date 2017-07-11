//
//  EventCodeRef.h
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef EventCodeRef_h
#define EventCodeRef_h

namespace CustomEventCode {
    static const std::string StartJourney           = "start_journey";
    static const std::string StarDestroy            = "star_destroy";
    static const std::string DeadForStarExplosion   = "dead_for_super_star_explosion";
    static const std::string JournalFinish          = "journal_finished";
    static const std::string EnergyRanOut           = "energy_ran_out_finish_journal";
    static const std::string PositiveExitJournal    = "player_positive_finish_journal";
    static const std::string CompleteJournal        = "player_finnaly_complete_journal";
    static const std::string UnlockNewChapter       = "player_unlock_new_chapter";
}

#endif /* EventCodeRef_h */
