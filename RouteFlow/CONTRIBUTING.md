## Submitting Pull Requests
* Discuss changes with the developers through GitHub Issues or the [Mailing List](https://groups.google.com/forum/#!forum/routeflow-discuss)
* Keep patches small, each as a single logical change.
* Patches shouldn't break things---even if they're fixed it a later patch.
* Code tidy-ups should be separate from functional changes.
* Check your patches before sending a pull request, ensure that there are no functionality regressions.
* Sign your patches off to indicate you have the right to submit the code.
* Send a pull request on GitHub so the community can review the changes.

## Signing Off Patches

The sign-off line at the end of a patch indicates that you agree to the
Developer's Certificate of Origin. It can be added by using the ``-s`` option
when committing code from git, or by adding a line in the following form at the
end of the commit message:

    Signed-off-by: Full Name <email@address.com>

### Developer's Certificate of Origin

To help track the author of a patch as well as the submission chain, and be
clear that the developer has authority to submit a patch for inclusion in
RouteFlow, please sign off your work.  The sign off certifies the following:

    Developer's Certificate of Origin 1.1

    By making a contribution to this project, I certify that:

    (a) The contribution was created in whole or in part by me and I
        have the right to submit it under the open source license
        indicated in the file; or

    (b) The contribution is based upon previous work that, to the best
        of my knowledge, is covered under an appropriate open source
        license and I have the right under that license to submit that
        work with modifications, whether created in whole or in part
        by me, under the same open source license (unless I am
        permitted to submit under a different license), as indicated
        in the file; or

    (c) The contribution was provided directly to me by some other
        person who certified (a), (b) or (c) and I have not modified
        it.

    (d) I understand and agree that this project and the contribution
        are public and that a record of the contribution (including all
        personal information I submit with it, including my sign-off) is
        maintained indefinitely and may be redistributed consistent with
        this project or the open source license(s) involved.

## RFProxy implementations

The RFProxy implementations are kept reasonably small so that it is easier to
run RouteFlow on multiple controller platforms. If you've ported RFProxy to a
new controller, get in touch on the mailinglist and we can add the
implementation to the core repository's _build.sh_ script, so that people can
install your RFProxy port directly from the main repository. We can also help
you migrate the implementation to this community hub for ongoing support.

RFProxy repositories must include a README being explicit about which version
of the controller platform is being used (eg, Ryu v1.2) to minimise confusion.
The RFProxy repository's master branch should work with the master branch of
RouteFlow core. RFProxy repositories may include a copy of the controller
platform. If this is included, the master branch should periodically
synchronised with upstream controller development.

If a new version of RouteFlow is tagged and released, we recommend updating your
RFProxy implementation to work against this tag, then creating a tag on your
RFProxy tree to indicate which version of RouteFlow it works with.
