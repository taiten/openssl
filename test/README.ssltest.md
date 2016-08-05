# SSL tests

SSL testcases are configured in the `ssl-tests` directory.

Each `ssl_*.conf.in` file contains a number of test configurations. These files
are used to generate testcases in the OpenSSL CONF format.

The precise test output can be dependent on the library configuration. The test
harness generates the output files on the fly.

However, for verification, we also include checked-in configuration outputs
corresponding to the default configuration. These testcases live in
`test/ssl-tests/*.conf` files. Therefore, whenever you're adding or updating a
generated test, you should run

```
$ ./config
$ cd test
$ TOP=.. perl -I testlib/ generate_ssl_tests.pl ssl-tests/my.conf.in \
  > ssl-tests/my.conf
```

where `my.conf.in` is your test input file.

For example, to generate the test cases in `ssl-tests/01-simple.conf.in`, do

```
$ TOP=.. perl generate_ssl_tests.pl ssl-tests/01-simple.conf.in > ssl-tests/01-simple.conf
```

For more details, see `ssl-tests/01-simple.conf.in` for an example.

## Configuring the test

First, give your test a name. The names do not have to be unique.

An example test input looks like this:

```
    {
        name => "test-default",
        server => { "CipherString" => "DEFAULT" },
        client => { "CipherString" => "DEFAULT" },
        test   => { "ExpectedResult" => "Success" },
    }
```

The test section supports the following options:

* ExpectedResult - expected handshake outcome. One of
  - Success - handshake success
  - ServerFail - serverside handshake failure
  - ClientFail - clientside handshake failure
  - InternalError - some other error

* ClientAlert, ServerAlert - expected alert. See `ssl_test_ctx.c` for known
  values.

* Protocol - expected negotiated protocol. One of
  SSLv3, TLSv1, TLSv1.1, TLSv1.2.

* ClientVerifyCallback - the client's custom certificate verify callback.
  Used to test callback behaviour. One of
  - None - no custom callback (default)
  - AcceptAll - accepts all certificates.
  - RejectAll - rejects all certificates.

* Method - the method to test. One of DTLS or TLS.

* ServerName - the server the client should attempt to connect to. One of
  - None - do not use SNI (default)
  - server1 - the initial context
  - server2 - the secondary context
  - invalid - an unknown context

* ServerNameCallback - the SNI switching callback to use
  - None - no callback (default)
  - IgnoreMismatch - continue the handshake on SNI mismatch
  - RejectMismatch - abort the handshake on SNI mismatch

* SessionTicketExpected - whether or not a session ticket is expected
  - Ignore - do not check for a session ticket (default)
  - Yes - a session ticket is expected
  - No - a session ticket is not expected
  - Broken - a special test case where the session ticket callback does not
    initialize crypto

* HandshakeMode - which handshake flavour to test:
  - Simple - plain handshake (default)
  - Resume - test resumption
  - (Renegotiate - test renegotiation, not yet implemented)

* ResumptionExpected - whether or not resumption is expected (Resume mode only)
  - Yes - resumed handshake
  - No - full handshake (default)

When HandshakeMode is Resume or Renegotiate, the original handshake is expected
to succeed. All configured test expectations are verified against the second handshake.

* ServerNPNProtocols, Server2NPNProtocols, ClientNPNProtocols, ExpectedNPNProtocol,
  ServerALPNProtocols, Server2ALPNProtocols, ClientALPNProtocols, ExpectedALPNProtocol -
  NPN and ALPN settings. Server and client protocols can be specified as a comma-separated list,
  and a callback with the recommended behaviour will be installed automatically.

## Configuring the client and server

The client and server configurations can be any valid `SSL_CTX`
configurations. For details, see the manpages for `SSL_CONF_cmd`.

Give your configurations as a dictionary of CONF commands, e.g.

```
server => {
    "CipherString" => "DEFAULT",
    "MinProtocol" => "TLSv1",
}
```

The following sections may optionally be defined:

* server2 - this section configures a secondary context that is selected via the
  ServerName test option. This context is used whenever a ServerNameCallback is
  specified. If the server2 section is not present, then the configuration
  matches server.
* resume_server - this section configures the client to resume its session
  against a different server. This context is used whenever HandshakeMode is
  Resume. If the resume_server section is not present, then the configuration
  matches server.
* resume_client - this section configures the client to resume its session with
  a different configuration. In practice this may occur when, for example,
  upgraded clients reuse sessions persisted on disk.  This context is used
  whenever HandshakeMode is Resume. If the resume_client section is not present,
  then the configuration matches client.

### Default server and client configurations

The default server certificate and CA files are added to the configurations
automatically. Server certificate verification is requested by default.

You can override these options by redefining them:

```
client => {
    "VerifyCAFile" => "/path/to/custom/file"
}
```

or by deleting them

```
client => {
    "VerifyCAFile" => undef
}
```

## Adding a test to the test harness

Add your configuration file to `test/recipes/80-test_ssl_new.t`.

## Running the tests with the test harness

```
HARNESS_VERBOSE=yes make TESTS=test_ssl_new test
```

## Running a test manually

These steps are only needed during development. End users should run `make test`
or follow the instructions above to run the SSL test suite.

To run an SSL test manually from the command line, the `TEST_CERTS_DIR`
environment variable to point to the location of the certs. E.g., from the root
OpenSSL directory, do

```
$ TEST_CERTS_DIR=test/certs test/ssl_test test/ssl-tests/01-simple.conf
```

or for shared builds

```
$ TEST_CERTS_DIR=test/certs util/shlib_wrap.sh test/ssl_test \
  test/ssl-tests/01-simple.conf
```

Note that the test expectations sometimes depend on the Configure settings. For
example, the negotiated protocol depends on the set of available (enabled)
protocols: a build with `enable-ssl3` has different test expectations than a
build with `no-ssl3`.

The Perl test harness automatically generates expected outputs, so users who
just run `make test` do not need any extra steps.

However, when running a test manually, keep in mind that the repository version
of the generated `test/ssl-tests/*.conf` correspond to expected outputs in with
the default Configure options. To run `ssl_test` manually from the command line
in a build with a different configuration, you may need to generate the right
`*.conf` file from the `*.conf.in` input first.
