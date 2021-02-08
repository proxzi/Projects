#!/usr/local/miniperl/miniperl -w
# +-------------------------------------------------------------------------+
# | DNSearch (Denwer Search)                                                |
# | Version: 1.3 [2005-02-12]                                               |
# +-------------------------------------------------------------------------+
# | Copyright � Anton Sushchev aka Ant <http://forum.dklab.ru/users/Ant/>   |
# +-------------------------------------------------------------------------+
# | Special thanks to:                                                      |
# |  � Dmitry Koteroff aka dk <http://forum.dklab.ru/users/DmitryKoteroff/> |
# |  � Ilya Lebedev aka WingedFox <http://forum.dklab.ru/users/WingedFox/>  |
# |  � <http://forum.dklab.ru/> and <http://Xpoint.ru/> (-;                 |
# +-------------------------------------------------------------------------+
# | Latest version: <http://debugger.ru/download/scripts/dnsearch/latest/>  |
# +-------------------------------------------------------------------------+


#use strict;
use Tools;
use Conf::DNSconf; # all config here

$| = 1;

# ���� ������ ���������� �������� � ����������, ���������������� ��������� 3 ������.
# ��������! ��� ����� � ��� ������ ���� ����������� ��������������� ������!
# use locale;
# use POSIX qw(locale_h);
# setlocale( LC_CTYPE, "Russian_Russia.1251" );

################################################################################
#*******************************************************************************
#* ����������� ���������� ����������
#*

# ��������� ������ �������.
%in = Tools::getQuery();

# ������ ������� ������.
if ( $in{ 'action' } ) {
	my %files = qw(css css.css js js.js xhtml_img xhtml10.gif css_img css.gif pb_img pb.gif);
	getFile( $files{ $in{ 'action' } } ) if $files{ $in{ 'action' } };
}

# ����������� ���������� ����������.
$action = exists $in{ 'action' } ? $in{ 'action' } : "";
$search = exists $in{ 'search' } ? $in{ 'search' } : "";
$dir    = exists $in{ 'dir'    } ? $in{ 'dir'    } : "";

# ������ �����.
( $dir_url, $dir_path ) = ();
if ( $dir ) {
	# ����� ������ ����������.
	if ( $PATHS{ $dir } ) {
		( $dir_path, $dir_url ) = ( $PATHS{ $dir }[ 1 ], $PATHS{ $dir }[ 2 ] );
		for ( $dir_path, $dir_url ) { s|\\|/|g; local $/ = '/'; chomp; $_ .= '/' }
	# ������ ���. ������.
	} else {
		print "Content-Type: text/html; charset=windows-1251\n\n";
		print "���������� ��� ������ �� ������� (�����? :-)."; exit;
	}
}

# ��������� ����� �, ���� ��� �����������, ������������� �������� �� ���������.
$logic       = $in{ 'logic'       } ? $in{ 'logic'       } : "and";
$register    = $in{ 'register'    } ? $in{ 'register'    } : "i";
$mode        = $in{ 'mode'        } ? $in{ 'mode'        } : "usual";
$current_str = $in{ 'current_str' } ? $in{ 'current_str' } : 0;
$in_find     = $in{ 'in_find'     } ? $in{ 'in_find'     } : 0;

# ������ �������, �� ������� ���������� ����������� � �.�.
$cache_buffer = undef;
if ( $action ) {
	$cache_buffer  = 'action='.$action.'&amp;search='.$search.'&amp;dir='.$dir."&amp;logic=".$logic."&amp;register=".$register."&amp;mode=".$mode;
	$cache_buffer .= '&amp;in_find='.$in_find if $in_find;
}

# ����� ����� ������ � �����������.
( $errors, $result ) = ( 0, 0 );

# ������, �� �������� ����� ������.
@mas_search = ();

# ��������, ������������ �� ������� XHTML.
my $type = $ENV{HTTP_ACCEPT} =~ m{\Qapplication/xhtml+xml\E(?!\s*;\s*q=0)} ? "application/xhtml+xml" : "text/html";
   $type = "Content-Type: $type; charset=windows-1251\n\n";

# ������ �������� (������ � ����� ����� ���� ������).
( $form, $header, $footer, $search_header, $search_center, $search_footer, $e1, $e2, $help ) = getTemplates();

################################################################################
#*******************************************************************************
#* ���� ���������
#*

# ���� �� ������� ������� �������, �� ������� ����� ��� ������ (� �����������).
if ( !$action ) {
	$header =~ s/\[search\]//ig;
	print $type.$header.'<div class="center">'.clearForm( $form ).'</div>'.$footer; exit;
# ������� ���� ����� ����� (��� include).
} elsif ( $action eq "form" ) {
	print "Content-Type: text/html; charset=windows-1251\n\n".clearForm( $form ); exit;
# ����� ������ �� ������.
} elsif ( $action eq "help" ) {
	$header =~ s/\[search\]/: ��� ������/ig;
	print $type.$header.'<div class="center">'.clearForm( $form ).'</div>'.$help.$footer; exit;
# ���� �� ������ ����� ������, ��... (-;
} elsif ( $action eq "search" ) {

	print $type;

	# ��������� �������������. (=
	$header =~ s/\[search\]/: $search/ig;
	$form   =~ s/\[finish\]/1/ig;
	my ( $cache_file, @files_to_search );

	# �������� ���������� (���� ������ �������, �� �������� ����� ������).
	@mas_search = varCheck();

	# �������� �� ���������� ������������� ����� ���������.
	if ( maxProcessCheck( 'begin' ) ) { print "${header}${e1}<b>����� ������������� ��������� ������ ��������� �����,<br />����������� ��������������� �������.<br />���������� ���������� �������.</b>${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}"; exit }

	# ��������� ����� �� ������������ ���.
	my $cache_mode = 0;
	if ( $CACHE_YES ) { ( $cache_mode, $cache_file, $dir_path, $dir_url, @files_to_search ) = cacheMode() }

	# ���� ������ � ��������� � ���� ��� �� ������, �� ������������ ���� � ������.
	if ( $in_find and !$cache_mode ) { ( $dir_path, $dir_url, @files_to_search ) = inFind() }

	# ������ � ��������� (������ � ���� �����!).
	{
		local $/ = 'p'; chomp $cache_file if $cache_file;
		for ( $form, $search_header, $search_footer ) {
			if ( $cache_file ) { s/\[in_find\]/${cache_file}p/ig; s/\[display_none\]//ig }
			else               { s/\[in_find\]//ig; s/\[display_none\]/display:none;/ig  }
		}
	}
	$search_header =~ s/\[form\]/$form/i || $search_footer =~ s/\[form\]/$form/i; # ����� ����� �������� ������ ���� ���

	# ��������� �����.
	print $header.$search_header;

	# ������ ������, � ������� ����� ������. ���� ���� �������������� ���, �� ���� ��� ����.
	if ( !$cache_mode and !$in_find ) { @files_to_search = searchList( $dir_path ) }

	# ����� �� ������ � ����� �����������.
	mainSearch( $cache_mode, $cache_file, @files_to_search );

	print '<div class="center">� ���������, ������ �� �������.</div>' if !$result;

	for ( $search_footer ) { s/\[result\]/$result/ig; s/\[errors\]/$errors/ig }
	print $search_footer.$footer;

	# �������� �� ���������� ������������� ����� ���������.
	maxProcessCheck( 'end' );

	exit;
}

################################################################################
#*******************************************************************************
#* �������
#*

# �������� �������������� ���������� ���������� ��������� ������.
sub maxProcessCheck {
	# �������� ��������.
	return if !$MAX_PROCESS_NUMBER;
	# ���� ��������.
	my $process_file = "$MAX_PROCESS_NUMBER_PATH/process.tmp";
	# ���� ���������.
	if ( -e $process_file and ( time() - ( stat $process_file )[ 9 ] ) > $MAX_PROCESS_NUMBER_TIME ) {
		unlink( $process_file )
	}
	# ������ ������.
	if ( $_[0] eq 'begin' ) {
		my $process = Tools::readTextFile( $process_file );
		if ( $process and $process >= $MAX_PROCESS_NUMBER ) {
			return 1; # error
		} else {
			unlink( $process_file );
			Tools::writeTextFile( $process_file, ++$process );
		}
	# ����� ������.
	} elsif ( $_[0] eq 'end' ) {
		my $process = Tools::readTextFile( $process_file );
		unlink( $process_file );
		Tools::writeTextFile( $process_file, --$process ) if ( $process and $process > 0 );
	}
	return 0; # ok
}

# ���������� ��� ����������� �������� �� �������� (���������� � �.�.).
sub varCheck {
	my @mas_search;

	# ������ ��������� ����������.
	if ( !-e $MAX_PROCESS_NUMBER_PATH ) {
		mkdir( $TMP_PATH, 0777 ) or die print "${header}${e1}<b>���������� ������� ��������� ���������� ($TMP_PATH):</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}${footer}";
	}

	# ���� ��������� �����������, �� ��������� ����� � �����.
	if ( $CACHE_YES and !-e $CACHE_PATH ) {
		mkdir( $CACHE_PATH, 0777 ) or die print "${header}${e1}<b>���������� ������� ���������� ��� ���� ($CACHE_PATH):</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}${footer}";
	}

	# ���� ��������� ����������� �����, �� ��������� ����� � �����.
	if ( $PATHS_CACHE and !-e $PATHS_CACHE_PATH ) {
		mkdir( $PATHS_CACHE_PATH, 0777 ) or die print "${header}${e1}<b>���������� ������� ���������� ��� ����������� ����� ($PATHS_CACHE_PATH):</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}${footer}";
	}

	# ���� � ���������� ���� ������, ��������� ����� ��� �������.
	if ( @ARCHIVE_FILE and !-e $ARCH_PATH ) {
		mkdir( $ARCH_PATH, 0777 ) or die print "${header}${e1}<b>���������� ������� ���������� ��� ������������� ������� ($ARCH_PATH):</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}${footer}";
	}

	# ���� �������� �������� ������������� ���������� ���������, ���������.
	if ( $MAX_PROCESS_NUMBER and !-e $MAX_PROCESS_NUMBER_PATH ) {
		mkdir( $MAX_PROCESS_NUMBER_PATH, 0777 ) or die print "${header}${e1}<b>���������� ������� ���������� ��� �������� ���������� ��������� ($MAX_PROCESS_NUMBER_PATH):</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}${footer}";
	}

	# ���������� �������� ������������� ����� ��� ������.
	if ( !-d $dir_path ) {
		print "${header}${e1}<b>���������� ��� ������ �� �������:</b><br />�".Tools::strXhtmlValid( $! )."�.${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}";
		exit;
	}

	# ��� ������ ��� ������.
	if ( $search eq '' or $search !~ /[^\s]/ ) { print "${header}${e1}<b>�� ������ ������ ��� ������.</b>${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}"; exit; }

	# ���� ������������ ������ ����� �RegEx� ��� ������, �� ��������� ��� ���������.
	if ( $mode eq "regex" ) {
		my $error = sub { "${header}${e1}<b>�������� ������ �� ������ �������� �� ������������:</b><br />�".Tools::strXhtmlValid( $_[0] )."�.${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}" };
		if ( $register eq "i" ) { $mas_search[ 0 ] = eval { qr/$search/i } || die print $error->( $@ ) }
		else                    { $mas_search[ 0 ] = eval { qr/$search/  } || die print $error->( $@ ) }
	# ���� ����� ��������.
	} else {
		$search =~ s/\s+/ /g;
		# ���� ������ ������� �� ����������
		# ����, ����� ������ �� ������ ������.
		if ( $search =~ / / and $logic ne "all" ) {
			for ( split( / /, $search ) ) {
				push( @mas_search, $_ ) if $_
			}
		# ���� ����� ����� ������ �������.
		} else { $mas_search[ 0 ] = $search }
	}

	# ��������� ���� � �������.
	for ( $CACHE_MAX_TIME, $PATHS_CACHE_MAX_TIME, $MAX_PROCESS_NUMBER_TIME ) { $_ *= 3600 }

	# ��������� ��������� � �����.
	for ( $CACHE_MAX_SIZE, $PATHS_CACHE_MAX_SIZE, $ARCH_MAX_SIZE, $ARCHIVE_FILE_MAX_SIZE ) { $_ *= 1048576 }

	if ( $in_find ) {
		# �������� ���������� ����� ����� ����.
		if ( $in_find !~ /^\d+\.tmp$/ ) { print "${header}${e1}<b>�������� ������ ����� ����.</b>${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}"; exit; }
		# �������� ������������� ����.
		if ( !-e "$CACHE_PATH/$in_find" ) { print "${header}${e1}<b>���������� �������� ���:</b><br />�".Tools::strXhtmlValid( $! )."�.<br /><br /><b>������ � ��������� ����������.</b>${e2}<br /><div class='center'>".clearForm( $form )."</div>${footer}"; exit }
	}

	return @mas_search;
}

# ��������� ���������� � ����� � ����� �� ������������ ���.
# ���� ������, �� ������ ����� ���� ��� ���� � ������ �������.
sub cacheMode {
	opendir( local *DIR, $CACHE_PATH );
		my @files = readdir( DIR );
	closedir( DIR );

	my $cache_size = 0;
	my ( $cache_mode, $cache_file, @cache_files, @cache_split, @files_to_search );

	for ( my $i = 0; $i <= $#files; $i++ ) {
		if ( !-d "$CACHE_PATH/$files[ $i ]" and $files[ $i ] =~ /^\d+\.tmp$/ ) {

			# ������������ ������ ����.
			$cache_size += ( stat( "$CACHE_PATH/$files[ $i ]" ) )[ 7 ];

			if ( !$CACHE_MAX_TIME or ( time() - ( stat "$CACHE_PATH/$files[ $i ]" )[ 9 ] ) < $CACHE_MAX_TIME ) {
				open( local *CACHE, "$CACHE_PATH/$files[ $i ]" ) or $errors++;
					if( <CACHE> eq $cache_buffer."\n" ) {
						# ��� ���� �� ������. ����� ��������.
						if ( !$cache_mode ) {
							$cache_mode = 1;            # �������� ������ ����
							$cache_file = $files[ $i ]; # ���� � ����� (��� ������� � ���������)

							# ������ ��� � ������� ���.
							for ( @cache_split = <CACHE> ) { chomp }
							( $dir_path, $dir_url ) = split( /\t/, shift( @cache_split ) );
							$errors = pop( @cache_split );
							$result = pop( @cache_split );
							for ( @cache_split ) {
								push( @files_to_search, [ split( /\t/ ) ] );
							}
						# ��� ��� ��� ������ => ��������.
						} else {
							close( CACHE ) or $errors++;
							unlink( "$CACHE_PATH/$files[ $i ]" );
							next;
						}
					} else {
						# ���������� ���-����� � ������ (��� ���������� ������������ ��������).
						push( @cache_files, "$CACHE_PATH/$files[ $i ]" )
					}
				close( CACHE ) or $errors++;
			} else { unlink( "$CACHE_PATH/$files[ $i ]" ) }
		}
	}

	# ���� ������ ���� ��������� �����������, �� ������ ��� ���������.
	# ���� � �������� �������� �0�, �� ������ �� ���������.
	if ( $CACHE_MAX_SIZE and $cache_size > $CACHE_MAX_SIZE ) { unlink( @cache_files ) }

	# ���� ��� ������ �� ���, �� ������ �����.
	if ( !$cache_mode ) {
		$cache_file = Tools::dozenRand.".tm";                                                    # �������� ������ ����� ����
		while ( -e "$CACHE_PATH/$cache_file" ) { $cache_file = Tools::dozenRand.".tm" }          # �� ������ ������ (-:
		Tools::writeTextFile( "$CACHE_PATH/$cache_file", "$cache_buffer\n$dir_path\t$dir_url" ); # �����...
	}

	return $cache_mode, $cache_file, $dir_path, $dir_url, @files_to_search;
}

# ���� ������� ����� ������� � ���������, ��
# �������� ������ ������ ��� ������, �� ����.
sub inFind {
	# ������ ��� ��� ������� � ���������.
	my $in_find_cache = Tools::readTextFile( "$CACHE_PATH/$in_find" );

	# �������.
	my @in_find_cache_split = split( /\n/, $in_find_cache );
	shift( @in_find_cache_split );
	( $dir_path, $dir_url ) = split( /\t/, shift( @in_find_cache_split ) );
	pop( @in_find_cache_split );
	pop( @in_find_cache_split );

	my @files_to_search;
	for ( @in_find_cache_split ) { push( @files_to_search, [ split( /\t/ ) ] ) }
	undef( @in_find_cache_split );

	# ��������� � ������� ������ ���� � ������.
	for ( @files_to_search ) { $_ = [ @$_[ 0 ], @$_[ 1 ] ] }

	return $dir_path, $dir_url, @files_to_search;
}

# ���� ���� ��� � ������ ��� ������, �� ������ ��.
# ���� ���, �� �������� ������� ����������� �����.
sub searchList {
	my $start_dir = $_[ 0 ];
	my $paths_cache_file = $PATHS_CACHE_PATH."/paths.tmp";
	my ( $start_dir_cache, $start_dir_time, %hash, @cache_files_to_search );

	if ( $PATHS_CACHE ) {
		# ���� ���� ����������.
		if ( -e $paths_cache_file ) {
			for ( split( /\n\n/, Tools::readTextFile( $paths_cache_file ) ) ) {
				@cache_files_to_search = split( /\n/ );
				( $start_dir_cache, $start_dir_time ) = split( /\|/, shift @cache_files_to_search );
				# ��������� �� ���������� ������.
				if ( !$PATHS_CACHE_MAX_TIME or ( time() - $start_dir_time < $PATHS_CACHE_MAX_TIME ) ) {
					$hash{ $start_dir_cache }[ 0 ] = $start_dir_time;
					for ( @cache_files_to_search ) {
						push( @{$hash{ $start_dir_cache }[ 1 ]}, [ split( /\|/, $_, 2 ) ] )
					}
				}
			}

			# ������� ���, ���� �������� ��� ������.
			if ( $PATHS_CACHE_MAX_SIZE and ( stat( $paths_cache_file ) )[ 7 ] > $PATHS_CACHE_MAX_SIZE ) { unlink( $paths_cache_file ) }
			# ���� ��� ������, ���������� ���.
			return @{$hash{ $start_dir }[ 1 ]} if $hash{ $start_dir };
		}

		# ���� ��� �� ������, �� ��������� �����.
		$hash{ $start_dir }[ 0 ] = time();
		my @files_to_search = filesList( $start_dir );
		for ( @files_to_search ) {
			push( @{$hash{ $start_dir }[ 1 ]}, $_ )
		}

		# ������� ������ ������ ���� � ����� �����.
		my $new_cache = "";
		unlink( $paths_cache_file );
		for ( keys %hash ) {
			$new_cache .= $_."|".$hash{ $_ }[ 0 ]."\n";
			for ( @{$hash{ $_ }[ 1 ]} ) {
				$new_cache .= @$_[ 0 ]."|".@$_[ 1 ]."\n"
			}
			$new_cache .= "\n";
		}
		chomp $new_cache; chomp $new_cache;
		Tools::writeTextFile( $paths_cache_file, $new_cache );
		return @files_to_search;
	} else { return filesList( $start_dir )	} # ���� ����� ��������, ���� �������� ����
}

# ������� �������� � ����� ������ ���� ������ ��
# ����� � �������� ���������� � � ��������������.
sub filesList {
	my $start_dir = $_[ 0 ];
	my ( @directories, @dir, @files_to_search, %archive_types, $arch_ext );
	my $number = 0;
	# ���� ����������.
	$directories[ 0 ] = $start_dir;
	for ( my $i = 0; $i <= $number; $i++ ) {
		opendir( local *DIR, $directories[ $i ] );
			@dir = readdir( DIR );
		closedir( DIR );
		for ( my $k = 0; $k <= $#dir; $k++ ) {
			if ( $i == 0 ) { local $/ = '/'; chomp $directories[ 0 ]; } # ��� �������� �����: �/�
			if ( -d "$directories[ $i ]/$dir[ $k ]" and no_search_in( $dir[ $k ], @NO_SEARCH_DIR ) ) {
				$directories[ ++$number ] = "$directories[ $i ]/$dir[ $k ]"
			}
		}
	}
	# ���� ����, �� ������ ���� � ������ �����������.
	if ( @ARCHIVE_FILE ) { %archive_types = Tools::parseTypes( 'Conf/archive.types' ) }
	# ���� ������.
	$directories[ 0 ] = $start_dir;
	@directories = sort( @directories );
	for ( my $i = 0; $i <= $number; $i++ ) {
		opendir( local *DIR, $directories[ $i ] );
			@dir = readdir( DIR );
		closedir( DIR );
		for ( my $k = 0; $k <= $#dir; $k++ ) {
			if ( $i == 0 ) { local $/ = '/'; chomp $directories[ 0 ]; } # ��� �������� �����: �/�
			if ( !-d "$directories[ $i ]/$dir[ $k ]" ) {
				# ��������� �� �����.
				if ( yes_search_in( $dir[ $k ], @ARCHIVE_FILE ) and ( $ARCHIVE_FILE_MAX_SIZE > -s "$directories[ $i ]/$dir[ $k ]" ) and ( $arch_ext = yes_search_in( $dir[ $k ], keys %archive_types ) ) ) {
					for ( archCheckUnpack( "$directories[ $i ]/$dir[ $k ]", $archive_types{ $arch_ext } ) ) {
						push( @files_to_search, [ $_, "$directories[ $i ]/$dir[ $k ]" ] )
					}
				# �������� ����.
				} elsif ( yes_search_in( $dir[ $k ], @YES_SEARCH_FILE ) and no_search_in( $dir[ $k ], @NO_SEARCH_FILE ) ) {
					push( @files_to_search, [ "$directories[ $i ]/$dir[ $k ]", "" ] )
				}
			}
		}
	}
	return @files_to_search;
}

# ��������� ���������� � �������������� ��������.
# ������� ��� ����� ���� �������� �����.
# ������������� ����� ���� ��� �����.
# ���������� ������ ���� � ������ ��� ������.
sub archCheckUnpack {
	my ( $archive, $archive_type ) = @_;
	my $archive_hash = $archive."_".( stat( $archive ) )[ 7 ];
	$archive_hash =~ s/[^A-Za-z�-��-�0-9]/_/g;

	# ���� ����� ������� ��������, �� ���������� ���������.
	my $arch_size = 0;
	opendir( local *DIR, $ARCH_PATH );
		for ( readdir( DIR ) ) {
			if ( -d "$ARCH_PATH/$_" and $_ ne '.' and $_ ne '..' ) {
				$arch_size += Tools::readTextFile( "$ARCH_PATH/$_/folder_size.ant" )
			}
		}
	closedir( DIR );
	if ( $ARCH_MAX_SIZE and $arch_size > $ARCH_MAX_SIZE ) {
		Tools::filesList( $ARCH_PATH, "1" );
		mkdir( $ARCH_PATH, 0777 );
	}

	opendir( local *DIR, $ARCH_PATH );
		my @dir = grep { /^${archive_hash}$/ } readdir( DIR );
	closedir( DIR );

	my @arch_files;
	if ( $dir[ 0 ] ) {
		( $arch_size, @arch_files ) = Tools::filesList( "$ARCH_PATH/$dir[ 0 ]" )
	} else {
		my $path = "$ARCH_PATH/$archive_hash";

		# �� ��� Win-��������� ��������� Unix-����.
		# ��������, �UnRar� ������� ������. /-:
		if ( $^O eq 'MSWin32' ) {
			$archive =~ s{/}{\\}g;
			$path =~ s{/}{\\}g;
			$path .= '\\';
		}

		$archive_type =~ s{\[file\]}{$archive}ig or return;
		$archive_type =~ s{\[dir\]}{$path}ig     or return;

		`$archive_type`; # �������� ������
		( $arch_size, @arch_files ) = Tools::filesList( "$ARCH_PATH/$archive_hash" );
		Tools::writeTextFile( "$ARCH_PATH/$archive_hash/folder_size.ant", $arch_size );
	}

	return grep { yes_search_in( $_, @YES_SEARCH_FILE ) and no_search_in( $_, @NO_SEARCH_FILE ) } @arch_files;
}

# �������� ��� ����������� ������� ��� ������.
# ����� ����� ������� ����������.
sub mainSearch {
	my ( $cache_mode, $cache_file, @files_to_search ) = @_;
	my ( $text, $arch_label, $hl, $title, $href, $match, $size, $count, $accord, $temp, $and );
	my ( @temp ); # ������, � ������� ������������ ��� ����������

	for ( my $i = 0; $i <= $#files_to_search; $i++ ) {
		# ���� ��� �� ������.
		if ( !$cache_mode ) {
			# ���������� �� � �������� �������... (-;
			$text = $arch_label = $hl = $title = $href = $match = $accord = $temp = "";
			$size = $count = $and = 0;

			# ��������� ������ �� ������ (read-only).
			# ���� �� ����, �� ���������� �����.
			if ( -r $files_to_search[ $i ] or -r $files_to_search[ $i ][ 0 ] ) {

				# �������� �� �����.
				$arch_label            = $files_to_search[ $i ][ 1 ]; # ���� � ������
				$files_to_search[ $i ] = $files_to_search[ $i ][ 0 ]; # ���� � �����

				$size = ( stat( $files_to_search[ $i ] ) )[ 7 ];       # ������ ����� � ������
				$text = Tools::readTextFile( $files_to_search[ $i ] ); # ������ ����
				$errors++ if !defined $text;                           # �� ������� �������� ����

				# ������� ���� � ������.
				# ����������� �� ���� ���������� <title>.
				( $title, $text ) = noTags( $text );

				# ���� ����� �������, �� ��������� �����.
				( $and, $hl, $title, $match, $count, $accord ) = textSearch( $title, $text );
				if ( $and ) {
					$temp = templatesParser( $files_to_search[ $i ], $arch_label, $hl, $title, $match, $size, $count, $accord ); # ������ �������
					$result++;
					push ( @temp, [ $accord, $count, $size, $temp ] );

					# ���� �������� ���, �� ����� � ����.
					if ( $CACHE_YES ) {
						# �������� ��� ������ ���������� �������.
						for ( $arch_label, $hl ,$title, $match, $size, $count ) {
							s/\s+/ /g
						}
						Tools::writeTextFile( "$CACHE_PATH/$cache_file", "\n$files_to_search[ $i ]\t$arch_label\t$hl\t$title\t$match\t$size\t$count\t$accord" );
					}
				}
			} else { $errors++ }
		# ���� �� ���� ���.
		} else {
			$temp   = templatesParser( @{$files_to_search[ $i ]} );
			$accord = @{$files_to_search[ $i ]}[ 7 ];
			$count  = @{$files_to_search[ $i ]}[ 6 ];
			$size   = @{$files_to_search[ $i ]}[ 5 ];
			push ( @temp, [ $accord, $count, $size, $temp ] );
		}
	}

	# ���� ����� �� ����� ���, ��...
	if ( $CACHE_YES and !$cache_mode ) {
		# ...����� �������������� ����� ���������� � ������.
		Tools::writeTextFile( "$CACHE_PATH/$cache_file", "\n".$result."\n".$errors );
		# ...��������������� ��������� ����, ��� ����� ����� ��� ��������� ��� ������.
		rename( "$CACHE_PATH/$cache_file", "$CACHE_PATH/$cache_file"."p" );
	}

	# ������� ����������.
	# ������� ����������.
	my $i = 0;
	for ( sort { $b->[ 0 ] <=> $a->[ 0 ] || $b->[ 1 ] <=> $a->[ 1 ] || $b->[ 2 ] <=> $a->[ 2 ] } @temp ) {
		$_->[ 3 ] =~ s/\[number\]/$i+1/ieg; # ������� ����������� ������
		if ( $RESULTS_PER_PAGE ) {
			if ( $RESULTS_PER_PAGE and ( $i >= $current_str ) and ( $i < $current_str + $RESULTS_PER_PAGE ) ) {
				print $_->[ 3 ]
			}
		} else { print $_->[ 3 ] }
		$i++;
	}

	# ������� � �������� ������� (���� ���� ��������� �� ��������).
	if ( $RESULTS_PER_PAGE and $result ) { resultsRuler() }
}

# ������������ ������.
sub textSearch {
	my ( $title, $text ) = @_;
	my ( $re, $c, $k, $count, $hit, %hash, %hl, $hl );
	my $and = 0;

	# ���������� �� ���� ��������� ������� ��� ������.
	for ( my $i = 0; $i <= $#mas_search; $i++ ) {
		# ���������� ����� �� �������� ��������. ���������� ������
		# ������� �������. ������������ ���������� ����������.
		if ( $mode ne "regex" ) {
			if ( $register eq "i" ) { $re = qr/\Q$mas_search[ $i ]\E/i }
			else                    { $re = qr/\Q$mas_search[ $i ]\E/  }
		} else                      { $re = qr/$mas_search[ $i ]/      }

		$title =~ s/(?:$re)+/<b>$&<\/b>/g;
		$c = 0;
		while ( $text =~ m/(?:$re)+/g ) {
			$hit = $&; # ������� ����������
			$hash{ $k++ } = [ pos( $text ) - length( $hit ), pos( $text ) ];
			$hit =~ /$re/;
			# ���� ����� ��������� �.*�, ��������, �� ��������� ����� ���� ������
			# ������������� � ��� �0� ��������. ��� ��� ���� ��������� ����� ��������.
			$c += length( $hit ) / length( $& ) if length( $& ) > 0;
			$hl{ lc $& }++;
		}
		if ( $c ) { $count += $c; $and++; }
	}

	# 10 ����� �������������� ���������� (��� ����������).
	$c = 0;
	for ( sort { $hl{ $b } <=> $hl{ $a } } keys %hl ) {
		if ( $c >= 10 ) { last } else { $c++ }
		$hl .= "$_=$hl{ $_ }&amp;";
	}
	if ( $hl ) { local $/ = '&amp;'; chomp $hl; }

	# ��������� �� �� �������.
	# ���� ������� ����� �Ȼ, �� ����� � �����.
	# ���� ������� ��, �� �������� ���.
	my $accord = 0;
	if ( $and - 1 < $#mas_search ) {
		return 0 if $logic eq "and"
	} else {
		$accord = 1
	}

	# ���������� �� ���� ��������� ��������.
	# ������������ ��������������� � ������� ���������.
	# ��������� ������� ���������.
	$text = overlayDelMarkerIns( $text, %hash );

	# ���������� ������ �����������.
	my $match = matchCheck( $text );

	return $and, $hl, $title, $match, $count, $accord;
}

# ...
# � �����-��������-���-������-����-�����������!
# � �!
# � �� ���� ���� �������!
# � �!
# (-:
sub overlayDelMarkerIns {
	my ( $text, %hash ) = @_;
	my ( $pre, $result_border_top, $result_border_bottom );

	for ( sort { $hash{ $a }[ 0 ] <=> $hash{ $b }[ 0 ] } keys %hash ) {
		# ���� ������ ������� ($pre �� ����������), ��
		# ���������� $pre � ��������� �� ������� ��������.
		# ��� �� ������������� ������� � ������ ������� (��� match).
		if ( !defined $pre ) {
			$pre = $_;
			$result_border_top = $hash{ $_ }[ 1 ] + $RESULT_BORDER;
			$result_border_bottom = $hash{ $_ }[ 0 ] - $RESULT_BORDER;
			$result_border_bottom = $result_border_bottom > 0 ? $result_border_bottom : 0;
			next;
		}

		# ����������� �������� ��������� �� ����� $RESULT_BORDER.
		if ( $hash{ $_ }[ 0 ] > $result_border_top ) { delete( $hash{ $_ } ); next; }

		# ��������� ��������������� � ��������� ��������.
		if ( $hash{ $_ }[ 0 ] < $hash{ $pre }[ 1 ] ) {
			if ( $hash{ $_ }[ 1 ] > $hash{ $pre }[ 1 ] ) {
				$hash{ $pre } = [ $hash{ $pre }[ 0 ], $hash{ $_ }[ 1 ] ];
				delete( $hash{ $_ } );
				next;
			} else {
				delete( $hash{ $_ } );
				next;
			}
		}

		$pre = $_;
	}

	# �������� �������� ��������� ����� ������.
	if ( $result_border_top and length( $text ) > $result_border_top ) {
		$text = substr( $text, 0, $result_border_top )."...";
	}

	# ��������� �� ����� ������� ����������
	# ������� ��������� �<� � �>�.
	my $c = 0;
	for ( sort { $hash{ $a }[ 0 ] <=> $hash{ $b }[ 0 ] } keys %hash ) {
		# ��� ������� ���������� �������, ����������� ��������� �� 2 �������.
		# ��� ���� � ���������� �������� ���������� �������� 1 ������
		# (������� ����� ������� != ������ �������).
		$hash{ $_ }[ 0 ] += $c * 2;
		$hash{ $_ }[ 1 ] += $c * 2 + 1;

		if ( length( $text ) >= $hash{ $_ }[ 0 ] ) {
			$text = substr( $text, 0, $hash{ $_ }[ 0 ] ).'<'.substr( $text, $hash{ $_ }[ 0 ] );
		}
		if ( length( $text ) >= $hash{ $_ }[ 1 ] ) {
			$text = substr( $text, 0, $hash{ $_ }[ 1 ] ).'>'.substr( $text, $hash{ $_ }[ 1 ] );
		}

		$c++;
	}

	# �������� �������� �������� ����� ������.
	if ( $result_border_bottom ) {
		$text = "...".substr( $text, $result_border_bottom );
	}

	return $text;
}

# ��������� �������� �������� ���-��.
sub matchCheck {
	# �������� �<� � �>� �� ������ ���� ���������.
	$_[ 0 ] =~ s/<(.*?)>/<b>$1<\/b>/img;

	# �������� ����������� ����.
	$_[ 0 ] =~ s/^([^<]*?)>/<b>$1<\/b>/gm;
	$_[ 0 ] =~ s/<([^>]*)$/<b>$1<\/b>/gm;

	return $_[ 0 ];
}

# ������� ������� � �������� �������.
sub resultsRuler {
	my $pages = Tools::ceil( $result / $RESULTS_PER_PAGE );
	my $path = $ENV{ 'SCRIPT_NAME' }."?".$cache_buffer.'&amp;current_str=';

	print "<br /><div class='center'>";
	if ( $current_str ) {
		print "<a href='".$path.do{ $current_str - $RESULTS_PER_PAGE }."' class='ruler' title='������� � ���������� ��������.'>&larr;&nbsp;����������</a>";
	}
	print "&nbsp;&nbsp;&nbsp;";
	if ( ( $current_str / $RESULTS_PER_PAGE ) + 1 != $pages ) {
		print "<a href='".$path.do{ $current_str + $RESULTS_PER_PAGE }."' class='ruler' title='������� � ��������� ��������.'>���������&nbsp;&rarr;</a>";
	}

	print "<br /><br /><div class='center' style='width:60%;margin:0 auto;'>";
	for ( my $i = 1; $i <= $pages; $i++ ) {
		if ( ( $current_str / $RESULTS_PER_PAGE ) + 1 == $i ) {
			print "<span id='ruler' title='������� ��������.'>$i</span>";
		} else {
			my $page = $RESULTS_PER_PAGE * ( $i - 1 );
			print " <a href='$path$page' class='ruler' title='����������: � ".do{ $page + 1 }."-� �� ".do{ $page + $RESULTS_PER_PAGE }."-� ��������.'>$i</a> ";
		}
	}
	print "</div></div>";
}

# �������� ���� � ������.
sub noTags {
	my ( $text ) = @_;
	my $title;
	# �������� ���������.
	( $title ) = $text =~ /<title\n*?>(.*?)<\/title\n*?>/ims;
	if ( !$title ) { $title = "��� ���������" }

	# �������� ���������, ��������, ������� � CSS.
	map { $text =~ s/<$_.*?\/$_\n*?>//imgs } qw(head script iframe frameset style);

	$text =~ s/<!--.*?--\n*?>//imgs; # �������� ������������
	$text =~ s/<.*?>//mgs;           # ������� ��� (!) ���� �� �������� (��������� ������ ����������)
	$text =~ s/<|>//g;               # ������� ��� ���������� �<� � �>� (�� ������ ������)
	$text =~ s/\s+/ /g;              # ��� ���������� ������� �������� �� ������� ������

	$text =~ s/&.{1,10};//g;         # For valid XHTML.
	$text =~ s/&//g;                 # The same.

	return $title, $text;
}

# ������ � ��������� ��� �������.
sub getTemplates {
	# ������ HTML-�������.
	my @mas = map { Tools::readTextFile( "templates/$_.html" ) } qw(form header footer search_header search search_footer error_header error_footer help);

	for ( @mas ) {
		s/^<!--.*?-->//sm; s/^\s+//;                # ������� ����� *������* ����������� (���)
		s/\[script_path\]/$ENV{ 'SCRIPT_NAME' }/ig; # ��������� ���� � �������
	}

	# ���� ��� ������.
	my $options;
	for ( sort { $a <=> $b } keys %PATHS ) {
		$options .= qq~<option value="$_">$PATHS{$_}[0]</option>\n~;
	}
	$mas[ 0 ] =~ s/\[paths\]/$options/ig;

	# ��� ����������� � ����� ������ ��������.
	for ( qw(search dir logic register mode) ) {
		$mas[ 0 ] =~ s/\[${_}_value\]/quotemeta( eval( '$'.$_ ) )/ieg;
	}

	return @mas;
}

# ������� ������ �����.
sub clearForm {
	$_[ 0 ] =~ s/\[in_find\]//ig;
	$_[ 0 ] =~ s/\[display_none\]/display:none;/ig;
	$_[ 0 ] =~ s/\[finish\]/0/ig;
	return $_[ 0 ];
}

# ������� ������� �������� ������ ��� ���.
sub templatesParser {
	my ( $file, $arch_label, $hl, $title, $match, $size, $count, $accord ) = @_;
	my ( $path, $href );

	# �� ���������� ������� (����� ��� �����-�� ������) ������� � ����������� � �������.
	if ( $arch_label eq "" ) {
		$path = $href = $file;
		# �������� �������� ���� ������ �� ����, �� �������� ���� ����� ����������.
		# ���� ������ ������������ � ������� �%PATHS� � �DNSconf.pm�.
		for ( $href, $path ) { s/$dir_path/$dir_url/i }
	} else {
		( $href ) = $ENV{ 'SCRIPT_NAME' } =~ /(.*)search\.pl/;
		$file =~ /^$ARCH_PATH(.*)$/;
		$href .= "viewer".$1."?".$hl;

		$path = $arch_label;
		$path =~ s/$dir_path/$dir_url/i;
	}

	1 while $size =~ s/(\d)(\d\d\d)(?!\d)/$1'$2/; # ����������� ������ ���� '1222333' � '1'222'333'

	my $temp = $search_center;
	$temp =~ s/\[href\]/$href/ig;
	$temp =~ s/\[title\]/$title/ig;
	$temp =~ s/\[match\]/$match/ig;
	$temp =~ s/\[path\]/$path ($size ����)/ig;
	$temp =~ s/\[count\]/$count/ig;
	if ( $accord ) { $temp =~ s/\[accord_color\]/#090/ig; $temp =~ s/\[accord_title\]/������� ��� �����./ig;    $temp =~ s/\[accord_text\]/������� ������������/ig   }
	else           { $temp =~ s/\[accord_color\]/#c00/ig; $temp =~ s/\[accord_title\]/������� �� ��� �����./ig; $temp =~ s/\[accord_text\]/��������� ������������/ig }

	return $temp;
}

# ���������� �0�, ���� ��������� �� ������� � ���� ��
# ����� ��������� �������. ���� �������, �� ���������� �1�.
sub no_search_in {
	my ( $item, @mas ) = @_;
	for ( @mas ) {
		if ( /^\(\?/ ) {
			return 0 if $item =~ $_;
		} elsif ( ( $item =~ /^\.\.$/ ) or ( $item =~ /^\.$/ ) ) {
			return 0
		} else {
			return 0 if $item =~ /$_$/i;
		}
	}
	return 1;
}

# ��� ������������ ���������� �0�. ��� ���������� � ��������� �������.
sub yes_search_in {
	my ( $item, @mas ) = @_;
	for ( @mas ) {
		if ( /^\(\?/ ) {
			return $& if $item =~ $_;
		} elsif ( ( $item =~ /^\.\.$/ ) or ( $item =~ /^\.$/ ) ) {
			return 0
		} else {
			return $_ if $item =~ /$_$/i;
		}
	}
	return 0;
}

# ������ ������.
sub getFile {
	# ����� ���������������� MIME-����.
	my %mime = Tools::parseTypes( "Conf/mime.types" );
	my ( $ext ) = $_[0] =~ /^.*\.(.*)$/;
	print "Content-type: $mime{$ext}\n\n" if $mime{$ext};                   # ���������
	binmode( STDOUT ); print Tools::readBinFile( "templates/$_[0]" ); exit; # ���������� �����
}

print "Content-Type: text/html; charset=windows-1251\n\n"; exit;
