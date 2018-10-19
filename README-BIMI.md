# XLL Update Cycle
_**QuantLibAddin-Old**_, _**QuantLib**_ and _**QuantLib-SWIG**_ are all *tracking repositories*.
Their **master** branch is an exact copy of the master branch in the upstream repositories.
Customisations are recorded on the **bimi** branch in each repository.

To update the repositories, you have to:
1. pull changes from the *upstream* repositories
2. integrate the changes into the *bimi* branches
3. push back to *origin* your changes

## Update Workflow
1. For each of the three repositories:
     1. align your local **master** branch
          1. `git checkout master`
          2. `git fetch origin master`
          3. `git status` ==> *Your branch is behind 'origin/master' by x commits, and can be fast-forwarded.*
          4. `git merge origin/master` ==> Should result in a FF
     2. merge changes from the **upstream** repository into your local master
          1. `git fetch upstream master`
          2. `git merge upstream/master` ==> Should result in a FF
          3. `git fetch upstream refs/tags/?_Upstream_Tag_Name_?:refs/tags/?_Local_Tag_Name_?`
     3. align your local **bimi** branch
          1. `git checkout bimi`
          2. `git fetch origin bimi`
          3. `git status` ==> *Your branch is behind 'origin/bimi' by x commits, and can be fast-forwarded.*
          4. `git merge origin/bimi` ==> Should result in a FF
     4. integrate the changes into the *bimi* branch
          1. `git merge --no-commit --no-ff _Local_Tag_Name_` (or `master`)
2. Resolve conflicts, do tests, ...
3. For each of the three repositories:
     1. commit your changes
          1. `git commit -m "Merge xxxx/yyy@zzzz into bimi."` where xxxx is the github upstream username, yyyy the
             upstream git repository name and zzzz the first 10 hex digits of the sha of the upstream last commit
             (e.g. lballabio/QuantLib@ff23624108)
     2. optionally add a release (annotated) tag
          1. `git tag -a bimi-rel-yyyymmdd -m "..."`
     3. push back all your changes
          1. `git push origin master`
          2. `git push origin bimi`

## First Time Setup
...
