def config = io.jenkins.plugins.analysis.warnings.groovy.ParserConfiguration.getInstance()

if(!config.contains('git-clang-format-parser2')){
    def newParser = new io.jenkins.plugins.analysis.warnings.groovy.GroovyParser(
        'git-clang-format-parser2',
        'Git Clang-Format Parser',
        '^diff\\s--git\\sa/([\\w/.]+)[\\S\\s\\n\\t\\r\\n\\f.]*?^@@\\s-(\\d+),(\\d+)[\\S\\s\\n\\t\\r\\n\\f.]*?^((?:^[+-].*$\\n?)+)',
        'return builder.setFileName(matcher.group(1)).setLineStart(Integer.parseInt(matcher.group(2))).setMessage(matcher.group(4)).buildOptional();',
        ""
    )
    config.addParser(newParser)
}


pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                // Checkout the source code from the repository
                checkout scm
            }
        }

        stage('Run git clang-format') {
            steps {
                script {
                    // Run git clang-format and store the result
                    def result = sh(script: 'git clang-format HEAD~1 --diff', returnStdout: true).trim()

                    // Print the result to the console
                    echo "git clang-format output:\n${result}"

                    // Fail the build if clang-format found issues
                    if (result.contains("clang-format did not modify any files")) {
                        echo "No formatting issues detected."
                    }
                }
            }
        }
    }

    post {
        always {
            recordIssues sourceCodeEncoding: 'UTF-8', tool: groovyScript(parserId: 'git-clang-format-parser2', reportEncoding:'UTF-8')


            // Clean up workspace after build
            cleanWs()
        }
    }
}
