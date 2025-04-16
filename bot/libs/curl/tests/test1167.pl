#!/usr/bin/env perl
#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
# SPDX-License-Identifier: curl
#
###########################################################################
#
# This script grew out of help from Przemyslaw Iskra and Balint Szilakszi
# a late evening in the #curl IRC channel.
#

use strict;
use warnings;
use vars qw($Cpreprocessor);

#
# configurehelp perl module is generated by configure script
#
my $rc = eval {
    require configurehelp;
    configurehelp->import(qw(
        $Cpreprocessor
    ));
    1;
};
# Set default values if configure has not generated a configurehelp.pm file.
# This is the case with cmake.
if (!$rc) {
    $Cpreprocessor = 'cpp';
}

my $verbose=0;

# verbose mode when -v is the first argument
if($ARGV[0] eq "-v") {
    $verbose=1;
    shift;
}

# we may get the dir root pointed out
my $root=$ARGV[0] || ".";

# need an include directory when building out-of-tree
my $i = ($ARGV[1]) ? "-I$ARGV[1] " : '';

my $incdir = "$root/include/curl";

my $summary=0;
my $misses=0;

my @syms;

sub scanenums {
    my ($file)=@_;
    my $skipit = 0;

    open H_IN, "-|", "$Cpreprocessor -DCURL_DISABLE_DEPRECATION $i$file" ||
        die "Cannot preprocess $file";
    while ( <H_IN> ) {
        my ($line, $linenum) = ($_, $.);
        if( /^#(line|) (\d+) \"(.*)\"/) {
            # if the included file isn't in our incdir, then we skip this section
            # until next #line
            #
            if($3 !~ /^$incdir/) {
                $skipit = 1;
                next;
            }
            # parse this!
            $skipit = 0;
            next;
        }
        if($skipit) {
            next;
        }
        if (/^#/) {
            next;
        }
        if ( /enum\s+(\S+\s+)?{/ .. /}/ ) {
            s/^\s+//;
            chomp;
            s/[,\s].*//;
            if(($_ !~ /\}(;|)/) &&
               ($_ ne "typedef") &&
               ($_ ne "enum") &&
               ($_ ne "=") &&
               ($_ !~ /^\d+$/) &&
               ($_ !~ /^[ \t]*$/)) {
                if($verbose) {
                    print "Source: $Cpreprocessor $i$file\n";
                    print "Symbol: $_\n";
                    print "Line #$linenum: $line\n\n";
                }
                push @syms, $_;
            }
        }
    }
    close H_IN || die "Error preprocessing $file";
}

sub scanheader {
    my ($f)=@_;
    scanenums($f);
    open H, "<$f";
    while(<H>) {
        my ($line, $linenum) = ($_, $.);
        if (/^ *# *define +([^ \n]*)/) {
            if($verbose) {
                print "Source: $f\n";
                print "Symbol: $1\n";
                print "Line #$linenum: $line\n\n";
            }
            push @syms, $1;
        }
    }
    close H;
}


opendir(my $dh, $incdir) || die "Can't opendir $incdir: $!";
my @hfiles = grep { /\.h$/ } readdir($dh);
closedir $dh;

for(@hfiles) {
    scanheader("$incdir/$_");
}

my $errors = 0;
for my $s (@syms) {
    if($s !~ /^(lib|)curl/i) {
        print "Bad symbols in public header files:\n" if(!$errors);
        $errors++;
        print "  $s\n";
    }
}
if($errors) {
    exit 1;
}
printf "%d fine symbols found\n", scalar(@syms);
