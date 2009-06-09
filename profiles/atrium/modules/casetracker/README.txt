// $Id: README.txt,v 1.22.2.1 2009/03/10 14:19:13 jmiccolis Exp $

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Features
 * Installation
 * Case Tracker Caveats!
 * Case Tracker URLs
 * Mail Sending and Receiving
 * Case Tracker Terminology


INTRODUCTION
------------

Current Maintainer: jmiccolis <http://drupal.org/user/31731>

Previous Maintainer: zero2one <http://drupal.org/user/105066>
Original Sponsor: Digital202
Original Developers: India-based team
Oversight: DaveNotik (http://drupal.org/user/18129/contact), killes, zero2one

This module enables teams to track outstanding cases which need resolution.
It provides e-mail notifications to participants about updates to cases and
is similar to many issue tracking systems.

This is a rewrite of the project.module and is very similar to that module
but varies in important ways. The project.module is specific to software
development and the need for a more generic issue tracker had been expressed.
As such, the casetracker.module only includes relevant functionality, but
also uses regular Drupal comments and integrates cleanly with Views, Organic
Groups, Mailhander, CCK, and more.


FEATURES
------------

Case Tracker enables teams to track outstanding cases. A case 
could be a bug report, a feature request, or a general task. You can also define 
new case types. Using Case Tracker, you can set the status of cases and their priority.

Case Tracker lets you have multiple projects and each case is tied to a project. 
The module includes default Project and Case node types. However, you can also define
existing node types to act as Project and Case node types in the administrative interface. 

Case Tracker includes three modules:
 * Case Tracker: Enables the handling of projects and their cases
 * Case Tracker Basic: Enables a basic project node type for use with Case Tracker
 * CT Mail: Enables mail sending and Mailhandler integration for Case Tracker

Case Tracker comes with two default Views:
 * casetracker_project_cases: Provides a list of cases that can be filtered by project, 
priority, status, or type. This view is used to generate a tab with a list of all "Cases"
 and a list of "My cases."
 * casetracker_project_options: Provides a list of all published projects. 


Using the administrative interface, you can use Case Tracker to:
 * Assign a user to all new cases by default
 * Assign a default case priority, status, and type to all cases
 * Define existing node types to act as Project and Case node types
 * Define new case states. Case state realms include priority, status, and type

Users can be assigned the following permissions at admin/user/permissions:
 * Create projects
 * Create cases
 * Edit own projects
 * Edit own cases

Case Tracker, and specifically casetracker_mail.module, has the ability to
send out custom emails whenever an issue is created or a comment posted, as
well as receive messages and post them as new cases or comments. 


INSTALLATION
------------

1. Copy the files to your sites/all/modules/ directory.

2. Enable the casetracker module at admin/modules.

3. Assign the project and case node type and other relevant case options at
   admin/settings/casetracker. Case Tracker ships with simplistic "Project"
   and "Case" types in its casetracker_basic.module; although you can use
   these, you will get stronger flexibility by assigning it to a
   content type of your own creation, or an Organic Group.

4. Customize case types, priorities, and states at admin/casetracker.

5. Enable permissions in admin/access.

Note: for more project.module-like functionality, try installing the
comment_upload.module and enabling comment attachments for case nodes.


CASE TRACKER CAVEATS!
---------------------

Some common gotchas which are, at the moment, "by design":

 * The "Last modified" value of Case Tracker cases is determined by the
   timestamp of the last comment attached to them (or, in the absence of
   a single comment, the node creation time). This requires that the
   comment.module (and node_comment_statistics table) are enabled and
   created. We CAN think of some use cases for not requiring comments on
   a case, but we think them edge cases and not enough to cater to. If
   you feel otherwise, don't hesitate to voice your opinion.

 * If you have node types with existing content (like already created
   Organic Groups), setting the Organic Group node type to be a Case
   Tracker project will NOT convert your existing content - the change
   will only apply to newly created Organic Groups. This may get fixed
   in the future: see http://drupal.org/node/65571 for the latest.


CASE TRACKER URLS
-----------------

The project based URLs we provide are briefly described below:

  /casetracker/projects
  /casetracker/projects/all
    Displays a list of all projects.

  /casetracker/projects/my
    Displays a list of projects created by the current user.

Case URL filtering is far more powerful, and supports a wide variety of
filters. "Unkeyed" filters are simply words or numbers that attempt to
satisfy the most common and relevant searches. For example, the word "my"
restricts the search to projects and cases the user has created, whereas
another unkeyed filter, "all", doesn't. Numbers like 13 or 15 usually refer
to a project or case ID: whatever makes the most sense at the time.

"Keyed" filters, however, have a name (the "key") and a value. To search
for cases that are of node type "casetracker_basic_case" only, you'd use a
keyed filter of "type:casetracker_basic_case". To show all cases that have
been created by users 23 and 35, you'd use "author:23,35", and so on.

The basic format of a Case Tracker case filter is:

  /casetracker/cases/PROJECT_FILTERS/CASE_FILTERS

The available project filters are described below:

    all   - show cases from all available projects.
    my    - show cases from projects the current user has created.
    ##    - show cases from only these project IDs.

The available case filters are described below:

  CASE UNKEYED FILTERS:
    all        - show all cases that match the project filters.
    my         - show current user's cases that match project filters.
    assigned   - show current user's assigned cases that match project filter.

  CASE KEYED FILTERS:
    assigned   - a comma separated list of uids that are assigned a case.
    author     - a comma separated list of uids that created a case.
    state      - a comma separated list of state IDs to filter by.
    type       - a comma separated list of node types to filter by.

Some EXAMPLES of these filters are below - these examples DO NOT
show every possible variation (as that would be rather timeconsuming):

  /casetracker/cases
  /casetracker/cases/all
  /casetracker/cases/all/all
    Display all cases for all projects.

  /casetracker/cases/my
  /casetracker/cases/my/all
    Display all cases in projects created by the current user.

  /casetracker/cases/all/my
    Display all cases created by the current user in all projects.

  /casetracker/cases/my/my
    Display all cases and projects created by the current user.

  /casetracker/cases/all/assigned
    Display all cases assigned to the current user in all projects.

  /casetracker/cases/14
  /casetracker/cases/14/all
    Display all cases assigned to project node ID 14.

  /casetracker/cases/all/state:1
    Display all cases with a state ID of 1.

  /casetracker/cases/my/state:4
    Display cases from my projects with a state ID of 4.

  /casetracker/cases/14/state:12
    Display cases from project node ID 14 with a state ID of 12.

But that's not all. To make things more deliciously confusing, you can
space-separate multiple filters and comma-separate values of a keyed
filter to get even more fine-turned searches:

  /casetracker/cases/all/assigned my
    Display cases from all projects which the current user
    has either opened, or which have been assigned to them.

  /casetracker/cases/my/my state:1
    Display cases in projects created by the current user that
    the current user has opened and which have a state ID of 1.

  /casetracker/cases/all/assigned my state:12,13
    Display cases in all projects that have been opened by the
    current user or have been assigned to the current user, and
    which have state IDs 12 or 13.


MAIL SENDING AND RECEIVING
--------------------------

Case Tracker, and specifically casetracker_mail.module, has the ability to
send out custom emails whenever an issue is created or a comment posted, as
well as receive messages and post them as new cases or comments. In practice,
this works great for simple node types, but breaks down under advanced configs
with CCK (specifically, emails are sent and received, but you
are unable to use any of your created fields as values). Additional funding
and development are required to hammer those issues out.

Creating cases or leaving comments through email requires the Mailhandler
module to be installed and configured properly. A new case can be created
with the following sample email sent to your Mailhandler mailbox:

 project_number: 500
 type: casetracker_basic_case
 case_title: This is a case title!
 assign_to: Morbus Iff
 case_status: open
 case_priority: 1-high
 case_type: bug

 This is the case body.

Emailed comments have no special characteristics, save that they must be
in reply to the original sent Case Tracker case email (the message IDs are
calculated and stored as a reference).

CASE TRACKER TERMINOLOGY
------------------------

Case Tracker assigns every project a unique project number that starts at 100
and increments by another hundred for each new project (200, 300, 400, etc.).
Similarly, cases receive individual case numbers that are unique to the
project and start at 1, incrementing by 1 for each new case (2, 3, 4, etc.)
within the project. Together, these two numbers combine to create a unique
case number in the Case Tracker system, such as 300-4 (project number 300,
case number 4). These numbers have no correlation to the Drupal node system.

We have attempted to standardize on the following terminology:

 * project ID: the node ID of the project.
 * project number: 100, 200, 300, as above.
 * case ID: the node ID of the case.
 * case number (individual): 1, 2, 3, etc. as above.
 * case number (combined): 100-1, 200-43, etc. as above.
 