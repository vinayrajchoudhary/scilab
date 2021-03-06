<?xml version='1.0' encoding='utf-8'?>
<xsl:stylesheet version ="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                ><!-- = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
                      ::
                      ::     M A I N   P A N E L :   G E N E R A L
                      ::
                 -->
  <xsl:template match="environment" mode="tooltip">Settings environment</xsl:template>
  <xsl:template match="environment">
    <Title text="Environment">
      <Grid>
        <Label gridx="1" gridy="1" weightx="0" text="Floating point exception: "/>
        <Panel gridx="2" gridy="1" weightx="1"/>
        <Panel gridx="3" gridy="1" weightx="0">
          <xsl:call-template name="Select">
            <xsl:with-param name="among">
              <option floating-point-exception="Produces an error"/>
              <option floating-point-exception="Produces a warning"/>
              <option floating-point-exception="Produces Inf or Nan"/>
            </xsl:with-param>
          </xsl:call-template>
        </Panel>
        <Label gridx="1" gridy="2" weightx="0" text="Printing format: "/>
        <Panel gridx="2" gridy="2" weightx="1"/>
        <Panel gridx="3" gridy="2" weightx="0">
          <xsl:call-template name="Select">
            <xsl:with-param name="among">
              <option printing-format="short"/>
              <option printing-format="long"/>
              <option printing-format="short e"/>
              <option printing-format="long e"/>
              <option printing-format="short g"/>
              <option printing-format="long g"/>
              <option printing-format="variable format"/>
            </xsl:with-param>
          </xsl:call-template>
        </Panel>
        <Label gridx="1" gridy="3" weightx="0" text="Width: "/>
        <Panel gridx="2" gridy="3" weightx="1"/>
        <NumericalSpinner gridx="3"
                          gridy="3"
                          weightx="0"
                          min-value = "1"
                          increment = "1"
                          length = "3"
                          listener = "ActionListener"
                          value = "{@width}">
          <actionPerformed choose="width">
            <xsl:call-template name="context"/>
          </actionPerformed>
        </NumericalSpinner>
      </Grid>
    </Title>
  </xsl:template>

  <xsl:template match="java-heap-memory" mode="tooltip"> and java heap size.</xsl:template>
  <xsl:template match="java-heap-memory">
    <VSpace height="10"/>
    <Title text="Java Heap Memory">
      <Grid>
        <Label text="Select the memory (in MB) available in Java: " gridx="1" gridy="1" anchor="baseline" weightx="0"/>
        <Panel gridx="2" gridy="1" weightx="1"/>
        <NumericalSpinner min-value = "128"
                          increment = "128"
                          length = "6"
                          listener = "ActionListener"
                          value = "{@heap-size}"
                          gridx="3" gridy="1" anchor="baseline" weightx="0">
          <actionPerformed choose="heap-size">
            <xsl:call-template name="context"/>
          </actionPerformed>
        </NumericalSpinner>
      </Grid>
    </Title>

  </xsl:template>

  <xsl:template match="tools">
    <VBox>
      <VSpace height="1"/>
      <HBox>
        <HSpace width="200"/>
        <VBox>
          <HBox>&lt;HTML&gt;&lt;I&gt;The following dialog boxes
          require user confirmation.
          </HBox>
          <HBox>&lt;HTML&gt;&lt;I&gt;Select a check
          box if you want that dialog box to appear.
          </HBox>
        </VBox>
      </HBox>

      <Title text="Confirmation dialogs">
        <Grid>
          <Label gridy="1" gridx="1" text="&lt;HTML&gt;&lt;B&gt;Dialog box description"/>
          <Label gridy="1" gridx="2" text="&lt;HTML&gt;&lt;B&gt;Tool"/>
          <Icon  gridy="1" gridx="3" listener="MouseListener">
            <xsl:attribute name="src">
              <xsl:choose>
                <xsl:when test="@order='ascending'">
                  <xsl:text>go-up.png</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>go-down.png</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <mouseClicked set="order">
              <xsl:attribute name="value">
                <xsl:choose>
                  <xsl:when test="@order='ascending'">
                    <xsl:text>descending</xsl:text>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>ascending</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:attribute>
              <xsl:call-template name="context"/>
            </mouseClicked>
          </Icon>
          <xsl:for-each select="tool">
            <xsl:sort order="{@order}" select="@name"/>
            <Checkbox
                gridy    = "{position() + 1}"
                gridx    = "1"
                listener = "ActionListener"
                checked  = "{@state}"
                text     = "{@description}"
                >
              <actionPerformed choose="state">
                <xsl:call-template name="context"/>
              </actionPerformed>
            </Checkbox>
            <Label
                gridy    = "{position() + 1}"
                gridx    = "2"
                text     = "{@name}"/>
          </xsl:for-each>
        </Grid>
      </Title>
      <Glue/>
      <HBox>
        <Glue/>
        <Button text="Select All" listener="ActionListener">
          <xsl:for-each select="tool">
            <actionPerformed set="state" value="checked">
              <xsl:call-template name="context"/>
            </actionPerformed>
          </xsl:for-each>
        </Button>
        <Glue/>
        <Button text="Clear All" listener="ActionListener">
          <xsl:for-each select="tool">
            <actionPerformed set="state" value="unchecked">
              <xsl:call-template name="context"/>
            </actionPerformed>
          </xsl:for-each>
        </Button>
        <Glue/>
      </HBox>
    </VBox>
  </xsl:template>

  <xsl:template match="actions">
    <xsl:variable name="name" select="@name"/>
    <xsl:variable name="current-item" select="action-folder[@name=$name]/action[number(@item)]"/>
    <Title text="Keys binding" fixed-height="false">
      <VBox fixed-height="false">
        <Grid>
          <Label gridy="1" gridx="1" gridwidth="2" text="Filter on action name:"/>
          <Entry gridy="2" gridx="1" gridwidth="2" text="{@filter}" listener="EntryListener">
            <entryChanged choose="filter">
              <xsl:call-template name="context"/>
            </entryChanged>
          </Entry>
        </Grid>
        <VSpace height="10"/>
        <Grid>
          <VBox gridx="1" gridy="1" weightx="0" anchor="north">
            <Label text="Component"/>
            <List item="{@name}" nb-visible-rows="4" listener="ActionListener">
              <actionPerformed choose="name">
                <xsl:call-template name="context"/>
              </actionPerformed>
              <xsl:for-each select="action-folder">
                <listElement name="{@name}"/>
              </xsl:for-each>
            </List>
          </VBox>
          <Panel gridx="2" gridy="1" weightx="0" width="30" height="1" fixed-width="true"/>
          <Grid gridx="3" gridy="1" weightx="1" anchor="north">
            <Label gridx="1" gridy="1" weightx="0" weighty="0" anchor="north" text="Name: "/>
            <Label gridx="2" gridy="1" weightx="0" weighty="0" anchor="west">
              <xsl:attribute name="text">
                <xsl:value-of select="$current-item/@name"/>
              </xsl:attribute>
            </Label>
            <Label gridx="1" gridy="2" weightx="0" weighty="0" anchor="north" text="Description: "/>
            <TextArea gridx="2" gridy="2" weightx="1" weighty="0" anchor="west" editable="false" rows="4">
              <xsl:attribute name="text">
                <xsl:value-of select="$current-item/@description"/>
              </xsl:attribute>
            </TextArea>
            <Label gridx="1" gridy="3" weightx="0" weighty="0" anchor="baseline" text="Binding: "/>
            <Entry gridx="2" gridy="3" weightx="0" weighty="0" anchor="baseline" listener="ActionListener">
              <xsl:attribute name="text">
                <xsl:value-of select="$current-item/@key"/>
              </xsl:attribute>
              <actionPerformed choose="key">
                <xsl:attribute name="context">
                  <xsl:for-each select="$current-item/ancestor-or-self::*">
                    <xsl:if test="not(.=/)">
                      <xsl:value-of select="count(preceding-sibling::*)+1"/>
                      <xsl:text>/</xsl:text>
                    </xsl:if>
                  </xsl:for-each>
                </xsl:attribute>
              </actionPerformed>
            </Entry>
          </Grid>
        </Grid>
        <VSpace height="10"/>
        <Table mode="select" listener="TableListener" fixed-height="false">
          <!-- we change this useless attribute (which is not an actuator) to force the table reload) -->
          <xsl:attribute name="name">
            <xsl:value-of select="concat($name,@filter)"/>
          </xsl:attribute>
          <tableSelect choose="item">
            <xsl:call-template name="context"/>
          </tableSelect>
          <xsl:for-each select="action-folder[@name=$name]/action[contains(
                                translate(@name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
                                translate(current()/@filter,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ'))]">
            <tableRow binding="{@key}" command="{@name}"/>
          </xsl:for-each>
          <tableCol title="Action name" attr="command"/>
          <tableCol title="Key binding" attr="binding"/>
        </Table>
        <Glue/>
      </VBox>
    </Title>
  </xsl:template>
</xsl:stylesheet>

