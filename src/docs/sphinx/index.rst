.. # Copyright 2019 Lawrence Livermore National Security, LLC and other
.. # Variorum Project Developers. See the top-level LICENSE file for details.
.. #
.. # SPDX-License-Identifier: MIT


========
Variorum
========

An extensible vendor-neutral library for exposing performance montoring and
control capabilities of low-level hardware knobs.

Introduction
============

Variorum is an extensible library for exposing monitor and control capabilities
of low-level hardware knobs. Variorum provides vendor-neutral APIs such that
the user can query or control hardware knobs without needing to know the
underlying vendor's implementation. These APIs enable HPC application
developers to gain a better understanding of performance through various
metrics for the devices contained within the node. Additionally, the APIs may
enable system software to control hardware knobs to optimize for a particular
goal.

Variorum focuses on ease of use and reduced integration burden for code teams:

- It includes examples which demonstrate how to use Variorum in a stand-alone
  program.
- It includes an example performance analysis sampler that runs alongside the
  application.


Variorum Project Resources
==========================

**Online Documentation**

http://software.llnl.gov/variorum

**Githib Source Repo**

http://github.com/llnl/variorum

**Issue Tracker**

http://github.com/llnl/variorum/issues

Contributors
============

- Peter Bailey
- Stephanie Brink (LLNL)
- Daniel Ellsworth
- Aniruddha Marathe (LLNL)
- Lauren Morita
- Tapasya Patki (LLNL)
- Barry Rountree (LLNL)
- Kathleen Shoga (LLNL)
- Scott Walker

Variorum Documentation
======================

.. toctree::

   QuickStart
   Variorum
   Releases
   Publications
   Licenses

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`