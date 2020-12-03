FROM continuumio/miniconda3

# [Option] Install zsh
ARG INSTALL_ZSH="true"
# [Option] Upgrade OS packages to their latest versions
ARG UPGRADE_PACKAGES="true"

# Install needed packages and setup non-root user. Use a separate RUN statement to add your own dependencies.
ENV USERNAME=code
ENV USER_UID=1000
ENV USER_GID=$USER_UID

COPY scripts/*.sh /tmp/scripts/
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    # Install common packages, non-root user, update yarn and install nvm
    && bash /tmp/scripts/common.sh "$INSTALL_ZSH" "$USERNAME" "$USER_UID" "$USER_GID" "$UPGRADE_PACKAGES" \
    # Clean up
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /root/.gnupg /tmp/scripts

COPY scripts/*.sh /tmp/scripts/
ENV PIPX_HOME=/usr/local/py-utils \
    PIPX_BIN_DIR=/usr/local/py-utils/bin
ENV PATH=${PATH}:${PIPX_BIN_DIR}
RUN bash /tmp/scripts/python.sh "none" "/opt/conda" "${PIPX_HOME}" "${USERNAME}" "false" \ 
    && apt-get clean -y && rm -rf /tmp/scripts