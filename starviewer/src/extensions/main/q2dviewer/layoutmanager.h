/*************************************************************************************
  Copyright (C) 2014 Laboratori de Gràfics i Imatge, Universitat de Girona &
  Institut de Diagnòstic per la Imatge.
  Girona 2014. All rights reserved.
  http://starviewer.udg.edu

  This file is part of the Starviewer (Medical Imaging Software) open source project.
  It is subject to the license terms in the LICENSE file found in the top-level
  directory of this distribution and at http://starviewer.udg.edu/license. No part of
  the Starviewer (Medical Imaging Software) open source project, including this file,
  may be copied, modified, propagated, or distributed except according to the
  terms contained in the LICENSE file.
 *************************************************************************************/

#ifndef UDGLAYOUTMANAGER_H
#define UDGLAYOUTMANAGER_H

#include <QObject>
#include <QSet>

namespace udg {

class Patient;
class Study;
class ViewersLayout;
class HangingProtocolManager;
class StudyLayoutConfig;
class HangingProtocol;

/**
    Manages hanging prootocols and automatic layouts for a given patient in a viewer's layout object
 */
class LayoutManager : public QObject {
Q_OBJECT
public:
    LayoutManager(Patient *patient, ViewersLayout *layout, QObject *parent = 0);
    ~LayoutManager();

    /// Sets up and initizalizes the layout for the current input
    void initialize();

    /// Cancels started operations such as downloading previous studies for an ordered hanging protocol
    void cancelOngoingOperations();

    /// Applies hanging protocols or automatic layouts depending on the user settings and the availability of the former
    void applyProperLayoutChoice();

    /// Applies a regular grid in a region of the layout depending on the current working situation.
    /// If no prior study is selected, the grid will occupy whole extent.
    /// Otherwise, it will occupy the current or prior study area depending on the position of the selected viewer.
    void setGrid(int rows, int columns);

public slots:

    /// Applies the next hanging protocol of the list if any was applied
    void applyNextHangingProtocol();

    /// Applies the previous hanging protocol of the list if any was applied
    void applyPreviousHangingProtocol();

    /// Set the working studies (current and prior studies).
    /// This will change the layout and the available hanging protocols.
    void setWorkingStudies(const QString &currentStudyUID, const QString &priorStudyUID);

    /// Set and applies the hanging protocol with the given identifier or object from the proper hanging protocol list
    /// In case a combined hanging protocol was applied, when a hanging protocol for the current or prior study is
    /// requested to be applied it implies that a new layout for the other study needs to be chosen as well.
    void setCurrentHangingProtocol(int hangingProtocolNumber);
    void setPriorHangingProtocol(int hangingProtocolNumber);
    void setCombinedHangingProtocol(int hangingProtocolNumber);

signals:
    /// Emits this signal when new hanging protocols are found for the current patient
    void hangingProtocolCandidatesFound(const QList<HangingProtocol*> &combined, const QList<HangingProtocol*> &current, const QList<HangingProtocol*> &prior);

private:
    /// True if current study has at least one modality with hanging protocol priority configured over automatic layouts, false otherwise.
    bool hasStudyAnyModalityWithHangingProtocolPriority(Study *study);

    /// Applies hanging protocols or automatic layouts depending on the user settings and the availability of the former
    void applyProperLayoutChoice(bool changeCurrentStudyLayout, bool changePriorStudyLayout);
    HangingProtocol *applyProperLayoutChoice(Study *study, const QList<HangingProtocol*> &hangingProtocols, const QRectF &studyLayoutGeometry);
    
    /// Hanging Protocols

    /// Applies the best matching hanging protocol from the available candidates found with searchHangingProtocols
    /// If there are no candidates to apply it returns NULL.
    HangingProtocol* applyBestHangingProtocol(const QList<HangingProtocol *> hangingProtocols, const QRectF &geometry);

    /// Auto Layouts

    /// Returns a list of StudyLayoutConfig corresponding to the given Study
    QList<StudyLayoutConfig> getLayoutCandidates(Study *study);

    /// Applies the proper layout candidate from the list for the given Study
    void applyLayoutCandidates(const QList<StudyLayoutConfig> &candidates, Study *study, const QRectF &geometry);
    void applyLayoutCandidates(const QList<StudyLayoutConfig> &candidates, Study *study, const QRectF &geometry, int rows, int columns);

    /// Returns the layout config that best suits for the given candidates and Study
    StudyLayoutConfig getBestLayoutCandidate(const QList<StudyLayoutConfig> &candidates, Study *study);

    /// Merges the StudyLayoutConfig items from the list into a single one. Criteria for merge will be as follows
    /// In case UnfoldType are different, LeftToRightFirst will prevail
    /// In case UnfoldDirectionType are different, UnfoldSeries will prevail
    /// If any exclusion criteria is included in one of the configurations, it will be included in the merged as well
    /// The maximum number of viewers will be the smallest value among all configurations
    StudyLayoutConfig getMergedStudyLayoutConfig(const QList<StudyLayoutConfig> &configurations);

    /// Sets and applies the hanging protocol with the given identifier or object
    HangingProtocol* setHangingProtocol(int hangingProtocolNumber, const QList<HangingProtocol*> &hangingProtocols, const QRectF &geometry);

    /// Fills the given parameters with the corresponding members depending on the selected viewer and the currently applied hanging protocol(s).
    /// The first parameter corresponds with m_*HangingProtocolApplied.
    /// The second parameter corresponds with m_*HangingProtocolCandidates.
    /// The third parameter is a reference to a pointer to a method and corresponds with set*HangingProtocol(int).
    void getHangingProtocolAppliedCandidatesAndSetterForSelectedViewer(HangingProtocol* &hangingProtocolApplied,
                                                                       QList<HangingProtocol*> &hangingProtocolCandidates,
                                                                       void (LayoutManager::* &setHangingProtocol)(int)) const;

private:
    /// Patient for the layout
    Patient *m_patient;

    /// Current and prior studies selected as working studies
    Study *m_currentStudy;
    Study *m_priorStudy;

    /// Layout object
    ViewersLayout *m_layout;

    /// Hanging Protocols manager
    HangingProtocolManager *m_hangingProtocolManager;

    /// Hanging protocol candidates for the current study, prior study and combined studies.
    QList<HangingProtocol*> m_currentStudyHangingProtocolCandidates;
    QList<HangingProtocol*> m_priorStudyHangingProtocolCandidates;
    QList<HangingProtocol*> m_combinedHangingProtocolCandidates;

    /// Current hanging protocol applied
    HangingProtocol *m_currentHangingProtocolApplied;
    /// Prior hanging protocol applied
    HangingProtocol *m_priorHangingProtocolApplied;
    /// Combined hanging protocol applied
    HangingProtocol *m_combinedHangingProtocolApplied;

};

} // end namespace udg

#endif
